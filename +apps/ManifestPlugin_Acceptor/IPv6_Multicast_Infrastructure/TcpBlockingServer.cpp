#include "pch.h"
#include "TcpBlockingServer.h"

namespace ipv6_multicast
{
   int TcpBlockingServer::CreateSocket() const
   {
      // Create socket for listening (client requests)
      const int listenSockDesc = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
      if (listenSockDesc == -1)
      {
         trace("socket() creation failed");
         exit(EXIT_FAILURE);
      }

      return listenSockDesc;
   }

   void TcpBlockingServer::ConfigureSocket(int socketDesc) const
   {
      // Set socket to reuse address
      int flag = 1;
      const int ret = setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&flag),
                                 sizeof flag);
      if (ret == -1)
      {
         trace("setsockopt() failure");
         exit(EXIT_FAILURE);
      }
   }

   sockaddr_in6 TcpBlockingServer::ConfigureSocketAddress(int port, const string& host, int socketDesc) const
   {
      // Init server address for IPv6
      struct sockaddr_in6 serverAddr{};
      memset(&serverAddr, 0, sizeof serverAddr);
      serverAddr.sin6_family = AF_INET6;
      serverAddr.sin6_addr = in6addr_any;
      serverAddr.sin6_port = htons(port);

      // Bind address and socket together
      int success = bind(socketDesc, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof serverAddr);
      if (success == -1)
      {
         trace("bind() failed");
         closesocket(socketDesc);
         exit(EXIT_FAILURE);
      }

      const int defaultBacklogCount = 10;
      success = listen(socketDesc, defaultBacklogCount);
      if (success == -1)
      {
         trace("listen() failed");
         closesocket(socketDesc);
         exit(EXIT_FAILURE);
      }

      return serverAddr;
   }

   bool TcpBlockingServer::InternalExchange(int socketDesc, const sockaddr_in6& sockAddr, std::atomic_bool& stop) const
   {
      struct sockaddr_in6 clientAddr{};
      socklen_t clientAddrLen = sizeof clientAddr;
      char strAddr[INET6_ADDRSTRLEN];
      const int messageBufferSize = 1400;
      const long accTimeoutSec = 1;
      trace(std::to_string(sockAddr.sin6_family) + " unused");

      while (!stop)
      {
         const select_status selectStat = GetMultiplexingStatus(socketDesc, accTimeoutSec, 0);
         switch (selectStat)
         {
         case select_status::select_error:
            trace("selection error");
            closesocket(socketDesc);
            return false;

         case select_status::not_in_set:
            trace("server socket not in read-ready set");
            closesocket(socketDesc);
            return false;

         case select_status::timeout:
            // 0 - timeout detected with no data
            trace("There is no data so far");
            continue;

         case select_status::has_accepted_client:
            // Ok - we have the data
            trace("New connection is about to be accepted");
            break;

         default:
            trace("unknown selection status");
            return false;
         }

         // Ok, now we know there is at least one client is going to read the data - do TCP handshake
         const int clientSockDesc = accept(socketDesc, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
         if (clientSockDesc == -1)
         {
            trace("accept() failed");
            closesocket(socketDesc);
            continue;
         }

         inet_ntop(AF_INET6, &clientAddr.sin6_addr, strAddr, sizeof strAddr);
         const unsigned short fmtAddr = ntohs(clientAddr.sin6_port);
         string toAddrStr = strAddr;
         trace("New connection from: " + toAddrStr + ":" + std::to_string(fmtAddr) + " ...");

         // Wait for data from client (NOTE: Also there should be timeout via select)
         char buf[messageBufferSize];
         int addrlen = sizeof clientAddr;
         int msgLen = recvfrom(
            clientSockDesc, buf, messageBufferSize, 0, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrlen);
         if (msgLen == -1)
         {
            trace("recvfrom() failed");
            closesocket(clientSockDesc);
            continue;
         }

         string clientDigest = TruncateResponse(buf, messageBufferSize, msgLen);
         trace("Client request " + clientDigest);
         string serverDigest = mman::LocalManifestDigest;
         string answer;
         answer = clientDigest == serverDigest
                     ? mman::ManifestResponseMsg
                     : mman::ManifestEmptyResponseMsg;

         // Send response to client (NOTE: Also there should be timeout via select)
         msgLen = sendto(clientSockDesc, answer.c_str(), answer.length(), 0,
                         reinterpret_cast<const struct sockaddr*>(&clientAddr), addrlen);
         if (msgLen == -1)
         {
            trace("write() failed");
            closesocket(clientSockDesc);
            continue;
         }

         // Do TCP tear down
         const int succeed = closesocket(clientSockDesc);
         if (succeed == -1)
         {
            trace("close() failed");
         }

         trace("Connection closed");
      }

      return true;
   }

   inline string TcpBlockingServer::TruncateResponse(char* buffer, const int bufferLen, const int messageLen)
   {
      if (messageLen < bufferLen)
      {
         int i = 0;
         while (i < messageLen && messageLen < bufferLen)
         {
            i++;
         }

         while (i < bufferLen)
         {
            buffer[i++] = '\0';
         }
      }

      string responseMsg = buffer;

      return responseMsg;
   }

   inline select_status TcpBlockingServer::GetMultiplexingStatus(int socketDesc, long seconds, long microseconds)
   {
      // Set for accept-ready sockets
      fd_set serverReadFds;
      FD_ZERO(&serverReadFds);
      FD_SET(socketDesc, &serverReadFds);

      // Setting server timeout
      struct timeval acceptTimeOut{};
      acceptTimeOut.tv_sec = seconds;
      acceptTimeOut.tv_usec = microseconds;

      // Find out the selection status
      const int srvSelectStat = select(socketDesc + 1, &serverReadFds, nullptr, nullptr, &acceptTimeOut);
      select_status selectStat =
         srvSelectStat != -1
            ? srvSelectStat > 0
                 ? selectStat = FD_ISSET(socketDesc, &serverReadFds)
                                   ? select_status::has_accepted_client
                                   : select_status::not_in_set
                 : selectStat = select_status::timeout
            : selectStat = select_status::select_error;

      return selectStat;
   }
}
