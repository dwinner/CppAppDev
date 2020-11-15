/**
 * IC emulation server for Manifest plugin
 */

#include "pch.h"
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

const std::string DefaultBroadcastIPv6Address = "::1/128";

bool initWinSock()
{
   WSADATA wsaData;
   const bool retVal = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0
                          ? false
                          : true;

   return retVal;
}

bool destroyWinSock()
{
   const int returnValue = WSACleanup();
   return returnValue != 0 ? false : true;
}

SOCKET createSocket()
{
   SOCKET socketFd = socket(AF_INET6, SOCK_STREAM, 0);
   return socketFd != INVALID_SOCKET ? socketFd : INVALID_SOCKET;
}

sockaddr_in6 configureServerAddress(const uint16_t tcpSrvPort = 29801)
{
   sockaddr_in6 stSrvAddress = {};

   ZeroMemory(&stSrvAddress, sizeof(stSrvAddress));
   stSrvAddress.sin6_family = AF_INET6;
   stSrvAddress.sin6_port = htons(tcpSrvPort);
   stSrvAddress.sin6_addr = in6addr_any;

   return stSrvAddress;
}

bool configureSocketOptions(SOCKET socketDesc, int32_t tcpHopLimit = 255)
{
   bool succeed;

   ipv6_mreq group = {};
   group.ipv6mr_interface = 0;
   int setOptRes = setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&group), sizeof(group));
   succeed = setOptRes < 0 ? false : true;
   if (succeed)
   {
      setOptRes = setsockopt(socketDesc, IPPROTO_IPV6, IPV6_UNICAST_HOPS, reinterpret_cast<char*>(&tcpHopLimit),
                             sizeof tcpHopLimit);
      succeed = setOptRes < 0 ? false : true;
   }

   return succeed;
}

bool bindSocket(SOCKET socketFd, sockaddr_in6 sockAddr)
{
   int bindResult = bind(socketFd, reinterpret_cast<struct sockaddr*>(&sockAddr), sizeof(struct sockaddr_in6));
   return bindResult < 0 ? false : true;
}

int quit(const std::string& errorMsg)
{
   std::cout << errorMsg.c_str();
   destroyWinSock();
   return EXIT_FAILURE;
}

bool listenSocket(SOCKET socketFd, uint32_t tcpSocketBacklogSize = 10U)
{
   int listenResult = listen(socketFd, tcpSocketBacklogSize);
   return listenResult < 0 ? false : true;
}

int main()
{
   // Initialize Winsock
   bool successStat = initWinSock();
   if (!successStat)
   {
      return quit("WSAStartup failed with error");
   }

   // Create socket and server address
   SOCKET socketDesc = createSocket();
   if (socketDesc == INVALID_SOCKET)
   {
      return quit("Failed to create socket");
   }

   // Construct server address
   sockaddr_in6 srvAddr = configureServerAddress();

   // Configure socket options
   successStat = configureSocketOptions(socketDesc);
   if (!successStat)
   {
      return quit("Error while setting socket options");
   }

   // Bind the socket
   successStat = bindSocket(socketDesc, srvAddr);
   if (!successStat)
   {
      return quit("Binding socket failure");
   }

   // Listen the socket
   successStat = listenSocket(socketDesc);
   if (!successStat)
   {
      return quit("Error listening the socket");
   }   

   fd_set xReadFds;
   FD_ZERO(&xReadFds);
   FD_SET(socketDesc, &xReadFds);
   // timeval stTimeout = {0, 100000U};
   int selectResult = select(static_cast<int>(socketDesc) + 1, &xReadFds, nullptr, nullptr, nullptr);
   if (selectResult > 0)
   {
      // Try accept
      int acceptResult = accept(socketDesc, nullptr, nullptr);
      if (acceptResult > 0)
      {
         // TODO: Apply communication
      }
   }

   destroyWinSock();

   return EXIT_SUCCESS;
}
