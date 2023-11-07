#include "network.h"

#if !defined(_WIN32)

#include <signal.h>

#endif

int main()
{

#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
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

   struct addrinfo *bindAddress;
   getaddrinfo(0, "8080", &hints, &bindAddress);

   printf("Creating socket...\n");
   SOCKET socketListen = socket(bindAddress->ai_family,
                                bindAddress->ai_socktype,
                                bindAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketListen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   printf("Binding socket to local address...\n");
   if (bind(socketListen,
            bindAddress->ai_addr, bindAddress->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   freeaddrinfo(bindAddress);

   printf("Listening...\n");
   if (listen(socketListen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   printf("Waiting for connection...\n");
   struct sockaddr_storage clientAddress;
   socklen_t clientLen = sizeof(clientAddress);
   SOCKET socketClient = accept(socketListen,
                                (struct sockaddr *) &clientAddress, &clientLen);
   if (!ISVALIDSOCKET(socketClient))
   {
      fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   printf("Client is connected.\n");
   printf("Waiting for client to disconnect.\n");

   int bytesReceived;
   while (1)
   {
      char read[1024];
      bytesReceived = recv(socketClient, read, 1024, 0);
      if (bytesReceived < 1)
      {
         break;
      }
      else
      {
         printf("Received %d bytes.\n", bytesReceived);
      }
   }

   printf("Client has disconnected.\n");
   printf("recv() returned %d\n", bytesReceived);
   printf("Attempting to send first data.\n");

   int sent = send(socketClient, "a", 1, 0);
   if (sent != 1)
   {
      fprintf(stderr, "first send() failed. (%d, %d)\n", sent, GETSOCKETERRNO());
   }

   printf("Attempting to send second data.\n");

   sent = send(socketClient, "a", 1, 0);
   if (sent != 1)
   {
      fprintf(stderr, "second send() failed. (%d, %d)\n", sent, GETSOCKETERRNO());
   }

   printf("Closing socket.\n");

   CLOSESOCKET(socketClient);

   printf("Finished.\n");

   return 0;
}

