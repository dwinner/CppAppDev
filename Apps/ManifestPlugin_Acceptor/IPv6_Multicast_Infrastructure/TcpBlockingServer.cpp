#include "pch.h"
#include "TcpBlockingServer.h"

namespace ipv6_multicast
{
   int TcpBlockingServer::CreateSocket()
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

   void TcpBlockingServer::ConfigureSocket(int socketDesc)
   {
      // Set socket to reuse address
      int flag = 1;
      const int ret = setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&flag),
                                 sizeof flag);
      if (ret == -1)
      {
#ifdef _DEBUG
         perror("setsockopt() failure");
#endif
         exit(EXIT_FAILURE);
      }
   }

   sockaddr_in6 TcpBlockingServer::ConfigureSocketAddress(int port, const string& host, int socketDesc)
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

   bool TcpBlockingServer::InternalExchange(int socketDesc, const sockaddr_in6& sockAddr)
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
}
