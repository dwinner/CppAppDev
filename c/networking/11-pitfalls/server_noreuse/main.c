/**
 * Try to start, shutdown and restart immediately.
 * You will see that the bind() calling is failed,
 * due to socket reusing is off.
 */

#include <stdbool.h>
#include "network.h"

int main()
{

#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return EXIT_FAILURE;
   }
#endif

   printf("Configuring local address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bindAddress;
   getaddrinfo(0, "8080", &hints, &bindAddress);

   printf("Creating socket...\n");
   SOCKET socketListen = socket(bindAddress->ai_family,
                                bindAddress->ai_socktype,
                                bindAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketListen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_SUCCESS;
   }

   printf("Binding socket to local address...\n");
   if (bind(socketListen,
            bindAddress->ai_addr, bindAddress->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_SUCCESS;
   }

   freeaddrinfo(bindAddress);

   printf("Listening...\n");
   if (listen(socketListen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_SUCCESS;
   }

   while (true)
   {
      printf("Waiting for connection...\n");
      struct sockaddr_storage client_address;
      socklen_t client_len = sizeof(client_address);
      SOCKET socket_client = accept(socketListen,
                                    (struct sockaddr *) &client_address, &client_len);
      if (!ISVALIDSOCKET(socket_client))
      {
         fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
         goto error;
      }

      printf("Client is connected.\n");
      CLOSESOCKET(socket_client);
   }

   error:
   return EXIT_FAILURE;

   return 0;
}
