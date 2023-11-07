/**
 * TCP simple chat example
 */

#include "../network.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
#if defined(_WIN32)
   WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

   printf("Configuring local address...\n");

   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bind_address;
   getaddrinfo(0, "8080", &hints, &bind_address);

   printf("Creating socket...\n");

   SOCKET socket_listen;
   socket_listen = socket(bind_address->ai_family,
                          bind_address->ai_socktype,
                          bind_address->ai_protocol);
   if (!ISVALIDSOCKET(socket_listen))
   {
      fprintf(stderr, "socket() failed. (%d)\n",
              GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Binding socket to local address...\n");

   if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n",
              GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   freeaddrinfo(bind_address);

   printf("Listening...\n");

   if (listen(socket_listen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n",
              GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   fd_set master;
   FD_ZERO(&master);
   FD_SET(socket_listen, &master);
   SOCKET max_socket = socket_listen;

   printf("Waiting for connections...\n");

   while (true)
   {
      fd_set reads;
      reads = master;
      if (select(max_socket + 1, &reads, 0, 0, 0) < 0)
      {
         fprintf(stderr, "select() failed. (%d)\n",
                 GETSOCKETERRNO());
         return EXIT_FAILURE;
      }

      SOCKET sock_rcv;
      for (sock_rcv = 1; sock_rcv <= max_socket; ++sock_rcv)
      {
         if (FD_ISSET(sock_rcv, &reads))
         {
            if (sock_rcv == socket_listen)
            {
               struct sockaddr_storage client_address;
               socklen_t client_len = sizeof(client_address);
               SOCKET socket_client = accept(socket_listen, (struct sockaddr *) &client_address, &client_len);
               if (!ISVALIDSOCKET(socket_client))
               {
                  fprintf(stderr, "accept() failed. (%d)\n",
                          GETSOCKETERRNO());
                  return EXIT_FAILURE;
               }

               FD_SET(socket_client, &master);
               if (socket_client > max_socket)
               {
                  max_socket = socket_client;
               }

               char address_buffer[100];
               getnameinfo((struct sockaddr *) &client_address,
                           client_len,
                           address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);

               printf("New connection from %s\n", address_buffer);
            }
            else
            {
               char read[1024];
               int bytes_received = recv(sock_rcv, read, 1024, 0);
               if (bytes_received < 1)
               {
                  FD_CLR(sock_rcv, &master);
                  CLOSESOCKET(sock_rcv);
                  continue;
               }

               SOCKET sock_to_send;
               for (sock_to_send = 1; sock_to_send <= max_socket; ++sock_to_send)
               {
                  if (FD_ISSET(sock_to_send, &master))
                  {
                     if (sock_to_send == socket_listen || sock_to_send == sock_rcv)
                     {
                        continue;
                     }
                     else
                     {
                        send(sock_to_send, read, bytes_received, 0);
                     }
                  }
               }
            }
         }
      }
   }

   printf("Closing listening socket...\n");
   CLOSESOCKET(socket_listen);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}
