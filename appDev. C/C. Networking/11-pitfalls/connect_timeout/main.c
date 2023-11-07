#include "network.h"

#if defined(_WIN32)
#define INPROGRESS WSAEWOULDBLOCK
#else
#define INPROGRESS EINPROGRESS
#endif

const char *get_error_text();

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
      fprintf(stderr, "usage: connect_timeout hostname port\n");
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
   char addressBuffer[100];
   char serviceBuffer[100];
   getnameinfo(peerAddress->ai_addr, peerAddress->ai_addrlen,
               addressBuffer, sizeof(addressBuffer),
               serviceBuffer, sizeof(serviceBuffer),
               NI_NUMERICHOST);
   printf("%s %s\n", addressBuffer, serviceBuffer);
   printf("Creating socket...\n");
   SOCKET socketPeer = socket(peerAddress->ai_family,
                              peerAddress->ai_socktype,
                              peerAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketPeer))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   // Set non blocking mode
#if defined(_WIN32)
   unsigned long nonblock = 1;
   ioctlsocket(socket_peer, FIONBIO, &nonblock);
#else
   int flags;
   flags = fcntl(socketPeer, F_GETFL, 0);
   fcntl(socketPeer, F_SETFL, flags | O_NONBLOCK);
#endif

   printf("Connecting...\n");
   int ret;
   if ((ret = connect(socketPeer, peerAddress->ai_addr, peerAddress->ai_addrlen))
       && GETSOCKETERRNO() != INPROGRESS)
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   freeaddrinfo(peerAddress);

   // Clear non blocking mode
#if defined(_WIN32)
   nonblock = 0;
   ioctlsocket(socket_peer, FIONBIO, &nonblock);
#else
   fcntl(socketPeer, F_SETFL, flags);
#endif

   if (ret == 0)
   {
      printf("Already connected.\n");
      printf("Perhaps non-blocking failed?\n");
   }
   else
   {
      printf("Waiting up to 5 seconds for connection...\n");

      fd_set set;
      FD_ZERO(&set);
      FD_SET(socketPeer, &set);

      struct timeval timeout;
      timeout.tv_sec = 5;
      timeout.tv_usec = 0;
      int selectResult = select(socketPeer + 1, 0, &set, 0, &timeout);
      if (selectResult == -1)
      {
         // Error occured
         printf("%s\n", get_error_text());
         return EXIT_FAILURE;
      }
      else if (selectResult == 0)
      {
         // Timeout expired
         printf("Timeout expired\n");
         return EXIT_FAILURE;
      }
      else
      {
         // OK: there are the total number of ready sockets
         printf("The number of sockets are: '%d'\n", selectResult);
      }
   }

   printf("Testing for connection...\n");
   if (send(socketPeer, "a", 1, 0) < 0)
   {
      printf("First send() failed. Connection was not successful.\n");
   }
   else
   {
      printf("First send() succeeded. Connection was successful.\n");
   }

   printf("Closing socket...\n");
   CLOSESOCKET(socketPeer);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}

const char *get_error_text()
{
#if defined(_WIN32)
   static char message[256] = {0};
   FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      0,
      WSAGetLastError(),
      0,
      message,
      256,
      0);
   char *nl = strrchr(message, '\n');
   if (nl)
   {
      *nl = 0;
   }

   return message;
#else
   return strerror(errno);
#endif
}
