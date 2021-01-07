/**
 * winSock2_Sample.cpp : Defines the entry point for the console application.
 */

#include <iostream>
#include "stdafx.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
   {
      return 1;
   }

   addrinfo hints{};
   hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
   hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

   // get ready to connect
   addrinfo* servInfo{}; // will point to the results
   const auto* const hostName = "www.google.com";
   const auto* const portNumber = "80";
   getaddrinfo(hostName, portNumber, &hints, &servInfo);

   const SOCKET sockfd
   {
      socket(
         servInfo->ai_family,
         servInfo->ai_socktype,
         servInfo->ai_protocol)
   };
   const int connectionResult
   {
      connect(
         sockfd,
         servInfo->ai_addr,
         servInfo->ai_addrlen)
   };
   if (connectionResult == -1)
   {
      cout << "Connection failed!" << endl;
   }
   else
   {
      cout << "Connection successful!" << endl;
   }

   freeaddrinfo(servInfo);

   WSACleanup();

   return 0;
}
