#include "network.h"

int main(int argc, char *argv[])
{

#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return 1;
   }
#endif

   if (argc < 3)
   {
      fprintf(stderr, "usage: big_send hostname port\n");
      return 1;
   }

   printf("Configuring remote address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peerAddress;
   if (getaddrinfo(argv[1], argv[2], &hints, &peerAddress))
   {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
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
      return 1;
   }

   printf("Connecting...\n");
   if (connect(socketPeer,
               peerAddress->ai_addr, peerAddress->ai_addrlen))
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
   }

   freeaddrinfo(peerAddress);

   printf("Connected.\n");
   printf("Sending lots of data.\n");

   const int sendSize = 10000;
   char *buffer;
   buffer = (char *) malloc(sendSize);
   if (!buffer)
   {
      fprintf(stderr, "Out of memory.\n");
      return 1;
   }

   int i;
   for (i = 1; i <= sendSize; ++i)
   {
      fd_set set;
      FD_ZERO(&set);
      FD_SET(socketPeer, &set);

      struct timeval timeout;
      timeout.tv_sec = 0;
      timeout.tv_usec = 0;
      select(socketPeer + 1, 0, &set, 0, &timeout);

      if (FD_ISSET(socketPeer, &set))
      {
         printf("Socket is ready to write.\n");
      }
      else
      {
         printf("Socket is not ready to write.\n");
      }

      printf("Sending %d bytes (%d total).\n", sendSize, i * sendSize);
      int r = send(socketPeer, buffer, sendSize, 0);
      if (r < 0)
      {
         fprintf(stderr, "send() failed. (%d)\n", GETSOCKETERRNO());
         return 1;
      }

      if (r != sendSize)
      {
         printf("send() only consumed %d bytes.\n", r);
         return 1;
      }
   }

   free(buffer);

   printf("Closing socket...\n");
   CLOSESOCKET(socketPeer);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");
   return 0;
}

