/**
 * IPv6 multicast example - receiver
 */

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#ifdef _WIN32
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")
using ssize_t = SSIZE_T;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

const int DefaultPort = 1900;
const std::string DefaultHost = "ff02::1:5";
#define MSGBUFSIZE   1400

int _tmain()
{
   struct sockaddr_in6 saddr, maddr;
   struct ipv6_mreq mreq;
   char buf[MSGBUFSIZE];
   ssize_t len;
   int sd, fd, rc, on = 1, flag = 0, hops = 255, ifidx = 0;
   struct timeval tv;
   fd_set fds;

#ifdef _WIN32
   WSADATA wsaData;
   if (WSAStartup(0x0101, &wsaData))
   {
      perror("WSAStartup");
      return 1;
   }
#endif   

   sd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
   if (sd < 0)
   {
      perror("socket");
      return 1;
   }

   if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)))
   {
      perror("setsockopt");
      return 1;
   }

   if (setsockopt(sd, IPPROTO_IPV6, IPV6_MULTICAST_IF, (const char*)&ifidx, sizeof(ifidx)))
   {
      perror("setsockopt");
      return 1;
   }

   if (setsockopt(sd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (const char*)&hops, sizeof(hops)))
   {
      perror("setsockopt");
      return 1;
   }

   if (setsockopt(sd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (const char*)&on, sizeof(on)))
   {
      perror("setsockopt");
      return 1;
   }

   memset(&saddr, 0, sizeof(saddr));
   saddr.sin6_family = AF_INET6;
   saddr.sin6_port = htons(DefaultPort);
   saddr.sin6_addr = in6addr_any;

   if (bind(sd, (struct sockaddr*)&saddr, sizeof(saddr)))
   {
      perror("bind");
      return 1;
   }

   memset(&maddr, 0, sizeof(maddr));
   inet_pton(AF_INET6, DefaultHost.c_str(), &maddr.sin6_addr);

   memcpy(&mreq.ipv6mr_multiaddr, &maddr.sin6_addr, sizeof(mreq.ipv6mr_multiaddr));
   mreq.ipv6mr_interface = ifidx;

   if (setsockopt(sd, IPPROTO_IPV6, IPV6_JOIN_GROUP, (const char*)&mreq, sizeof(mreq)))
   {
      perror("setsockopt");
      printf("%d", WSAGetLastError());
      return 1;
   }

   FD_ZERO(&fds);
   FD_SET(sd, &fds);
   tv.tv_sec = 10;
   tv.tv_usec = 0;   
   
   while (true)
   {
      if (flag)
      {
         rc = select(sd + 1, &fds, nullptr, nullptr, nullptr/*&tv*/);
         if (!rc)
         {
            break;
         }

         tv.tv_sec = 10;
         tv.tv_usec = 0;
      }
      
      int addrlen = sizeof(saddr);
      len = recvfrom(sd, buf, MSGBUFSIZE, 0, (struct sockaddr *) &saddr, &addrlen);
      buf[len] = '\0';      

      if (!len)
      {
         break;
      }

      if (len < 0)
      {
         perror("read");
         return 1;
      }
      
      printf("Received: %s\n", buf);

      flag++;
   }

   closesocket(sd);   

#ifdef _WIN32
   WSACleanup();
#endif

   return 0;
}
