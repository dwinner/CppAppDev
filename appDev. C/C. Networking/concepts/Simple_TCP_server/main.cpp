/**
 * Stream socket server demo
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <csignal>

/**
 * The port users will be connecting to
 */
#define PORT "3490"

/**
 * How many pending connections queue will hold
 */
#define BACKLOG 10

void sig_child_handler(int s);

/**
 * @brief Get sockaddr, IPv4 or IPv6:
 * @param socket_addr socket struct pointer entity
 * @return IPv4 or IPv6 socket internet address
 */
void *get_in_addr(struct sockaddr *socket_addr);

int main()
{
   // listen on sock_fd, new connection on new_fd
   int sock_fd = 0;
   struct addrinfo hints{}, *servInfo, *p;
   struct sockaddr_storage their_addr{}; // connector's address information
   socklen_t sin_size;
   struct sigaction sa{};
   int yes = 1;
   char s[INET6_ADDRSTRLEN];
   int rv;

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE; // use my IP

   if ((rv = getaddrinfo(nullptr, PORT, &hints, &servInfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return EXIT_FAILURE;
   }

   // loop through all the results and bind to the first we can
   for (p = servInfo; p != nullptr; p = p->ai_next)
   {
      if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
      {
         perror("server: socket");
         continue;
      }

      if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
      {
         perror("setsockopt");
         exit(EXIT_FAILURE);
      }

      if (bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1)
      {
         close(sock_fd);
         perror("server: bind");
         continue;
      }

      break;
   }

   // all done with this structure
   freeaddrinfo(servInfo);

   if (p == nullptr)
   {
      fprintf(stderr, "server: failed to bind\n");
      exit(EXIT_FAILURE);
   }

   if (listen(sock_fd, BACKLOG) == -1)
   {
      perror("listen");
      exit(EXIT_FAILURE);
   }

   // reap all dead processes
   sa.sa_handler = sig_child_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;
   if (sigaction(SIGCHLD, &sa, nullptr) == -1)
   {
      perror("sigaction");
      exit(EXIT_FAILURE);
   }

   printf("server: waiting for connections...\n");

   // main accept loop
   while (true)
   {
      sin_size = sizeof their_addr;
      const int new_fd = accept(sock_fd, (struct sockaddr *) &their_addr, &sin_size);
      if (new_fd == -1)
      {
         perror("accept");
         continue;
      }

      inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
      printf("server: got connection from %s\n", s);

      if (!fork()) // this is the child process
      {
         close(sock_fd); // child doesn't need the listener
         const char *srvMsg = "Hello, from Linux server";
         if (send(new_fd, srvMsg, strlen(srvMsg), 0) == -1)
         {
            perror("send");
         }

         close(new_fd);
         exit(EXIT_SUCCESS);
      }

      close(new_fd); // parent doesn't need this
   }

   //return EXIT_SUCCESS;
}

void sig_child_handler(int s)
{
   (void) s; // quiet unused variable warning

   // waitpid() might overwrite errno, so we save restore it:
   const int saved_errno = errno;
   while (waitpid(-1, nullptr, WNOHANG) > 0)
   {
   }

   errno = saved_errno;
}

void *get_in_addr(struct sockaddr *socket_addr)
{
   if (socket_addr->sa_family == AF_INET)
   {
      struct in_addr *sin_addr = &((struct sockaddr_in *) socket_addr)->sin_addr;
      return sin_addr;
   }

   return &((struct sockaddr_in6 *) socket_addr)->sin6_addr;
}
