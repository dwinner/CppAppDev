/**
 * datagram "client" demo
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_PORT "4950"

int main(int argc, char* argv[])
{
   int sock_fd = 0;
   struct addrinfo hints{}, *server_info, *p_lnk_idx;
   int return_value;
   int numbytes;

   if (argc != 3)
   {
      fprintf(stderr, "usage: talker hostname message\n");
      exit(1);
   }

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_DGRAM;

   if ((return_value = getaddrinfo(argv[1], SERVER_PORT, &hints, &server_info)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(return_value));
      return 1;
   }

   // loop through all the results and make a socket
   for (p_lnk_idx = server_info; p_lnk_idx != nullptr; p_lnk_idx = p_lnk_idx->ai_next)
   {
      if ((sock_fd = socket(p_lnk_idx->ai_family, p_lnk_idx->ai_socktype,
                            p_lnk_idx->ai_protocol)) == -1)
      {
         perror("talker: socket");
         continue;
      }

      break;
   }

   if (p_lnk_idx == nullptr)
   {
      fprintf(stderr, "talker: failed to create socket\n");
      return 2;
   }

   if ((numbytes = sendto(sock_fd, argv[2], strlen(argv[2]), 0,
                          p_lnk_idx->ai_addr, p_lnk_idx->ai_addrlen)) == -1)
   {
      perror("talker: sendto");
      exit(1);
   }

   freeaddrinfo(server_info);

   printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
   close(sock_fd);

   return 0;
}
