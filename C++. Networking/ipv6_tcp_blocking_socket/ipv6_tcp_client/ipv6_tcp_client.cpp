#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#define SERVER_PORT  1991
#define MSGBUFSIZE   1400
const char* address = "::1";

int _tmain()
{
   int sock_fd = -1;
   struct sockaddr_in6 server_addr;
   int ret;
   char ch = 'a';   

#ifdef _WIN32
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData))
   {
      perror("WSAStartup");
      return 1;
   }
#endif

   /* Create socket for communication with server */
   sock_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
   if (sock_fd == -1)
   {
      perror("socket()");
      return EXIT_FAILURE;
   }

   /* Connect to server running on localhost */
   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin6_family = AF_INET6;   
   inet_pton(AF_INET6, address, &server_addr.sin6_addr);
   server_addr.sin6_port = htons(SERVER_PORT);

   /* Try to do TCP handshake with server */
   ret = connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
   if (ret == -1)
   {
      printf("connect failed with error: %d\n", WSAGetLastError());      
      closesocket(sock_fd);
      return EXIT_FAILURE;
   }

   /* Send data to server */
   char buf[MSGBUFSIZE];
   int addrlen = sizeof(server_addr);
   int len = sendto(sock_fd, buf, MSGBUFSIZE, 0, (const struct sockaddr*)&server_addr, addrlen);
   if (len == -1)
   {
      perror("write");
      closesocket(sock_fd);
      return EXIT_FAILURE;
   }

   buf[len] = '\0';

   /* Wait for data from server */
   ret = recvfrom(sock_fd, buf, MSGBUFSIZE, 0, (struct sockaddr*)&server_addr, &addrlen);
   if (ret == -1)
   {
      perror("read()");
      closesocket(sock_fd);
      return EXIT_FAILURE;
   }

   printf("Received %c from server\n", ch);

   /* DO TCP teardown */
   ret = closesocket(sock_fd);
   if (ret == -1)
   {
      perror("close()");
      return EXIT_FAILURE;
   }

#ifdef _WIN32
   WSACleanup();
#endif

   return EXIT_SUCCESS;
}
