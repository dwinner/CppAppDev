#include "network.h"

int main(int argc, char *argv[])
{

#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return EXIT_FAILURE;
   }
#endif

   if (argc < 3)
   {
      fprintf(stderr, "usage: connect_blocking hostname port\n");
      return EXIT_FAILURE;
   }

   printf("Configuring remote address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peerAddress;
   if (getaddrinfo(argv[1], argv[2], &hints, &peerAddress))
   {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Remote address is: ");
   char address_buffer[100];
   char service_buffer[100];
   getnameinfo(peerAddress->ai_addr, peerAddress->ai_addrlen,
               address_buffer, sizeof(address_buffer),
               service_buffer, sizeof(service_buffer),
               NI_NUMERICHOST);
   printf("%s %s\n", address_buffer, service_buffer);

   printf("Creating socket...\n");
   SOCKET socketPeer = socket(peerAddress->ai_family,
                              peerAddress->ai_socktype,
                              peerAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketPeer))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Connecting...\n");
   if (connect(socketPeer,
               peerAddress->ai_addr, peerAddress->ai_addrlen))
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   freeaddrinfo(peerAddress);

   printf("Connected.\n");
   printf("Closing socket...\n");
   CLOSESOCKET(socketPeer);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");
   return 0;
}
