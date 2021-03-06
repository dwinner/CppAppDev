// Datagram sockets "server" demo

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * @brief The port users will be connecting to
 */
#define MYPORT "4950"

#define MAXBUFLEN 100

void* get_in_addr(struct sockaddr* socket_address)
{
   if (socket_address->sa_family == AF_INET)
   {
      return &reinterpret_cast<sockaddr_in*>(socket_address)->sin_addr;
   }

   return &reinterpret_cast<sockaddr_in6*>(socket_address)->sin6_addr;
}

int main()
{
   auto sock_fd = 0;
   struct addrinfo hints{}, *server_info, *p_linked_idx;
   int return_value;
   ssize_t numbytes;
   struct sockaddr_storage their_addr{};
   char data_buffer[MAXBUFLEN];
   socklen_t address_length;
   char from_address[INET6_ADDRSTRLEN];

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
   hints.ai_socktype = SOCK_DGRAM;
   hints.ai_flags = AI_PASSIVE; // use my IP

   if ((return_value = getaddrinfo(nullptr,MYPORT, &hints, &server_info)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(return_value));
      return 1;
   }

   // loop through all the results and bind to the first we can
   for (p_linked_idx = server_info; p_linked_idx != nullptr; p_linked_idx = p_linked_idx->ai_next)
   {
      if ((sock_fd = socket(p_linked_idx->ai_family, p_linked_idx->ai_socktype, p_linked_idx->ai_protocol)) == -1)
      {
         perror("listener: socket");
         continue;
      }

      if (bind(sock_fd, p_linked_idx->ai_addr, p_linked_idx->ai_addrlen) == -1)
      {
         close(sock_fd);
         perror("listener: bind");
         continue;
      }

      break;
   }

   if (p_linked_idx == nullptr)
   {
      fprintf(stderr, "listener: failed to bind socket\n");
      return 2;
   }

   freeaddrinfo(server_info);

   printf("listener: waiting to recvfrom...\n");

   address_length = sizeof their_addr;
   if ((numbytes = recvfrom(sock_fd, data_buffer, MAXBUFLEN - 1, 0,
                            (struct sockaddr*)&their_addr, &address_length)) == -1)
   {
      perror("recvfrom");
      exit(1);
   }

   printf("listener: got packet from %s\n",
          inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr*)&their_addr), from_address,
                    sizeof from_address));
   printf("listener: packet is %zd bytes long\n",
          numbytes);
   data_buffer[numbytes] = '\0';
   printf("listener: packet contains \"%s\"\n", data_buffer);

   close(sock_fd);

   return 0;
}
