#include <iostream>

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "mman/manifest_storage.hpp"

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

#define SERVER_PORT        1991

void clean_wsa();

void init_wsa();

int create_socket();

void configure_socket(int socketDesc);

sockaddr_in6 configure_socket_address(int port, int socketDesc);

void exchange_data(int socketDesc, sockaddr_in6 sockAddr);

int _tmain()
{
   init_wsa();

   const int listenSockDesc = create_socket();
   configure_socket(listenSockDesc);
   const struct sockaddr_in6 sockAddr = configure_socket_address(SERVER_PORT, listenSockDesc);
   exchange_data(listenSockDesc, sockAddr);
   closesocket(listenSockDesc);
   clean_wsa();

   return EXIT_SUCCESS;
}

void clean_wsa()
{
#ifdef _WIN32
   WSACleanup();
#endif
}

void init_wsa()
{
#ifdef _WIN32
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData))
   {
#ifdef _DEBUG
      perror("WSAStartup");
#endif

      exit(EXIT_FAILURE);
   }
#endif
}

int create_socket()
{
   // Create socket for listening (client requests)
   const int listenSockDesc = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
   if (listenSockDesc == -1)
   {
#ifdef _DEBUG
      perror("socket() creation failed");
#endif
      exit(EXIT_FAILURE);
   }

   return listenSockDesc;
}

void configure_socket(const int socketDesc)
{
   // Set socket to reuse address
   int flag = 1;
   const int ret = setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&flag), sizeof flag);
   if (ret == -1)
   {
#ifdef _DEBUG
      perror("setsockopt() failure");
#endif
      exit(EXIT_FAILURE);
   }
}

sockaddr_in6 configure_socket_address(int port, int socketDesc)
{
   // Init server address for IPv6
   struct sockaddr_in6 serverAddr{};
   memset(&serverAddr, 0, sizeof(serverAddr));
   serverAddr.sin6_family = AF_INET6;
   serverAddr.sin6_addr = in6addr_any;
   serverAddr.sin6_port = htons(port);

   // Bind address and socket together
   int success = bind(socketDesc, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof serverAddr);
   if (success == -1)
   {
#ifdef _DEBUG
      perror("bind() failed");
#endif

      closesocket(socketDesc);
      exit(EXIT_FAILURE);
   }

   const int defaultBacklogCount = 10;
   success = listen(socketDesc, defaultBacklogCount);
   if (success == -1)
   {
#ifdef _DEBUG
      perror("listen() failed");
#endif

      closesocket(socketDesc);
      exit(EXIT_FAILURE);
   }

   return serverAddr;
}

void exchange_data(const int socketDesc, sockaddr_in6 sockAddr)
{
   struct sockaddr_in6 clientAddr{};
   socklen_t clientAddrLen = sizeof clientAddr;
   char strAddr[INET6_ADDRSTRLEN];
   const int messageBufferSize = 1400;

   using namespace std;

   while (true)
   {
      // Do TCP handshake with client
      const int clientSockDesc = accept(socketDesc, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
      if (clientSockDesc == -1)
      {
#ifdef _DEBUG
         perror("accept() failed");
#endif

         closesocket(socketDesc);
         exit(EXIT_FAILURE);
      }

      inet_ntop(AF_INET6, &clientAddr.sin6_addr, strAddr, sizeof strAddr);

#ifdef _DEBUG
      cout << "New connection from: " << strAddr << ":" << ntohs(clientAddr.sin6_port) << " ..." << endl;
#endif

      // Wait for data from client
      char buf[messageBufferSize];
      int addrlen = sizeof clientAddr;
      int msgLen = recvfrom(
         clientSockDesc, buf, messageBufferSize, 0, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrlen);
      if (msgLen == -1)
      {
#ifdef _DEBUG
         perror("recvfrom()");
#endif

         closesocket(clientSockDesc);
         continue;
      }

      // Truncate the buffer
      if (msgLen < messageBufferSize)
      {
         int i = 0;
         while (i < msgLen && msgLen < messageBufferSize)
         {
            i++;
         }

         while (i < messageBufferSize)
         {
            buf[i++] = '\0';
         }
      }

      // TODO: make business logic for protocol

#ifdef _DEBUG
      cout << "Client request " << buf;
#endif

      string answer = mman::ManifestResponseMsg;

      // Send response to client
      msgLen = sendto(clientSockDesc, answer.c_str(), answer.length(), 0,
                      reinterpret_cast<const struct sockaddr*>(&clientAddr), addrlen);
      if (msgLen == -1)
      {
#ifdef _DEBUG
         perror("write() failed");
#endif

         closesocket(clientSockDesc);
         continue;
      }

      // Do TCP tear down
      const int succeed = closesocket(clientSockDesc);
      if (succeed == -1)
      {
#ifdef _DEBUG
         perror("close() failed");
#endif
      }

#ifdef _DEBUG
      std::cout << "Connection closed" << std::endl;      
#endif
   }
}
