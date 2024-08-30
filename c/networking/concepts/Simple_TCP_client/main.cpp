/**
 * A stream socket client demo
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * @brief the port client will be connecting to
 */
#define PORT "3490"

/**
 * max number of bytes we can get at once
 */
#define MAXDATASIZE 100

/**
 * @brief get sockaddr, IPv4 or IPv6
 * @param socket_addr socket address
 * @return inet address
 */
void* get_in_addr(struct sockaddr* socket_addr);

int main(int argc, char* argv[])
{
   int sock_fd = 0;
   ssize_t numbytes;
   char buf[MAXDATASIZE];
   struct addrinfo hints{}, *servinfo, *p;
   int rv;
   char s[INET6_ADDRSTRLEN];

   if (argc != 2)
   {
      fprintf(stderr, "usage: client hostname\n");
      exit(EXIT_FAILURE);
   }

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;

   if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return EXIT_FAILURE;
   }

   // loop through all the results and connect to the first we can
   for (p = servinfo; p != nullptr; p = p->ai_next)
   {
      if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
      {
         perror("client: socket");
         continue;
      }

      if (connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1)
      {
         perror("client: connect");
         close(sock_fd);
         continue;
      }

      break;
   }

   if (p == nullptr)
   {
      fprintf(stderr, "client: failed to connect\n");
      return 2;
   }

   inet_ntop(p->ai_family, get_in_addr(static_cast<sockaddr*>(p->ai_addr)), s, sizeof s);
   printf("client: connecting to %s\n", s);

   // all done with this structure
   freeaddrinfo(servinfo);

   if ((numbytes = recv(sock_fd, buf,MAXDATASIZE - 1, 0)) == -1)
   {
      perror("recv");
      exit(EXIT_FAILURE);
   }

   buf[numbytes] = '\0';

   printf("client: received '%s'\n", buf);
   close(sock_fd);

   return 0;
}

void* get_in_addr(struct sockaddr* socket_addr)
{
   if (socket_addr->sa_family == AF_INET)
   {
      return &reinterpret_cast<sockaddr_in*>(socket_addr)->sin_addr;
   }

   return &reinterpret_cast<sockaddr_in6*>(socket_addr)->sin6_addr;
}
