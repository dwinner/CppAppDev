/**
 * telnot.c -- Not telnet, but can be used in place of telnet for
 *             the guide demos.
 *
 * This doesn't implement the telnet protocol in the least.
 *
 * Usage: telnot hostname port
 *
 * Then type things and hit RETURN to send them. (It uses the current
 * terminal line discipline, which is probably line-buffered so nothing
 * will get sent until you hit RETURN.) It will print things to
 * standard output as it receives them.
 *
 * Hit ^C to break out.
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <arpa/inet.h>

constexpr int buffer_size = 1024;

/**
 * Get a sockaddr, IPv4 or IPv6
 */
void* get_in_addr(struct sockaddr* socket_addr)
{
   if (socket_addr->sa_family == AF_INET)
   {
      return &reinterpret_cast<sockaddr_in*>(socket_addr)->sin_addr;
   }

   return &reinterpret_cast<sockaddr_in6*>(socket_addr)->sin6_addr;
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
   int sock_fd = 0;
   struct addrinfo hints{}, *srv_info, *p_idx;
   int ret_val;
   char ip_addr[INET6_ADDRSTRLEN];

   if (argc != 3)
   {
      fprintf(stderr, "usage: telnot hostname port\n");
      exit(1);
   }

   char* hostname = argv[1];
   char* port = argv[2];

   // Try to connect

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;

   if ((ret_val = getaddrinfo(hostname, port, &hints, &srv_info)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret_val));
      return 1;
   }

   // loop through all the results and connect to the first we can
   for (p_idx = srv_info; p_idx != nullptr; p_idx = p_idx->ai_next)
   {
      sock_fd = socket(p_idx->ai_family, p_idx->ai_socktype, p_idx->ai_protocol);
      if (sock_fd == -1)
      {         
         continue;
      }

      if (connect(sock_fd, p_idx->ai_addr, p_idx->ai_addrlen) == -1)
      {       
         close(sock_fd);
         continue;
      }

      break;
   }

   if (p_idx == nullptr)
   {
      fprintf(stderr, "client: failed to connect\n");
      return 2;
   }

   // Connected!

   inet_ntop(p_idx->ai_family,
             get_in_addr(static_cast<sockaddr*>(p_idx->ai_addr)),
             ip_addr,
             sizeof ip_addr);

   printf("Connected to %s port %s\n", ip_addr, port);
   printf("Hit ^C to exit\n");

   freeaddrinfo(srv_info); // All done with this structure

   // Poll stdin and sockfd for incoming data (ready-to-read)
   struct pollfd fds[2];

   fds[0].fd = 0;
   fds[0].events = POLLIN;

   fds[1].fd = sock_fd;
   fds[1].events = POLLIN;

   // Main loop
   for (;;)
   {
      if (poll(fds, 2, -1) == -1)
      {
         perror("poll");
         exit(1);
      }

      for (auto& fd : fds)
      {
         // Check for ready-to-read
         if (fd.revents & POLLIN)
         {
            int readbytes, writebytes;
            char buf[buffer_size];

            // Compute where to write data. If we're stdin (0),
            // we'll write to the sockfd. If we're the sockfd, we'll
            // write to stdout (1).
            const auto outfd = fd.fd == 0
               ? sock_fd
               : 1;

            // We use read() and write() in here since those work on
            // all fds, not just sockets. send() and recv() would
            // fail on stdin and stdout since they're not sockets.
            if ((readbytes = read(fd.fd, buf, buffer_size)) == -1)
            {
               perror("read");
               exit(2);
            }

            char* p = buf;
            int remainingbytes = readbytes;

            // Write all data out
            while (remainingbytes > 0)
            {
               if ((writebytes = write(outfd, p, remainingbytes)) == -1)
               {
                  perror("write");
                  exit(2);
               }

               p += writebytes;
               remainingbytes -= writebytes;
            }
         }
      }
   }

   // Not reached--use ^C to exit.
   // return 0;
}
