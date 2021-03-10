#include <stdlib.h>
#include <netdb.h>
#include "network_utils.h"

void *get_in_addr(struct sockaddr *p_socket_address)
{
   if (p_socket_address->sa_family == AF_INET)
   {
      return &(((struct sockaddr_in *) p_socket_address)->sin_addr);
   }

   return &(((struct sockaddr_in6 *) p_socket_address)->sin6_addr);
}

void set_stream_address(struct addrinfo **addr_info, const char *port_num)
{
   int return_val;
   struct addrinfo hints;
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;
   if ((return_val = getaddrinfo(NULL, port_num, &hints, addr_info)) != 0)
   {
      fprintf(stderr, "select_server: %s\n", gai_strerror(return_val));
      exit(EXIT_FAILURE);
   }
}

int get_server_listener(struct addrinfo *addr_info)
{
   int srv_sock_desc = -1; // listening socket descriptor

   int yes = 1;  // for setsockopt() SO_REUSEADDR, below
   struct addrinfo *p_lnk_idx;
   for (p_lnk_idx = addr_info;
        p_lnk_idx != NULL;
        p_lnk_idx = p_lnk_idx->ai_next)
   {
      srv_sock_desc = socket(p_lnk_idx->ai_family, p_lnk_idx->ai_socktype, p_lnk_idx->ai_protocol);
      if (srv_sock_desc < 0)
      {
         continue;
      }

      // lose the pesky "address already in use" error message
      setsockopt(srv_sock_desc, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

      if (bind(srv_sock_desc, p_lnk_idx->ai_addr, p_lnk_idx->ai_addrlen) < 0)
      {
         close(srv_sock_desc);
         continue;
      }

      break;
   }

   // if we got here, it means we didn't get bound
   if (p_lnk_idx == NULL)
   {
      srv_sock_desc = -1;
   }

   return srv_sock_desc;
}
