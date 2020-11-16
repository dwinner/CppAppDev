/**
 * IPv6 multicast example - sender
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

const int delay_secs = 1;
const int DefaultPort = 1900;
const std::string DefaultHost = "ff02::1:5";
#define MSGBUFSIZE   1400

int _tmain()
{
   struct sockaddr_in6 saddr;
   struct ipv6_mreq mreq;
   const char* buf = "Hi from multicast via IPv6";
   ssize_t len = 1;
   int sd, fd, on = 1, hops = 255, ifidx = 0;

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
      printf("%d", WSAGetLastError());
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

   memset(&saddr, 0, sizeof(struct sockaddr_in6));
   saddr.sin6_family = AF_INET6;
   saddr.sin6_port = htons(DefaultPort);
   inet_pton(AF_INET6, DefaultHost.c_str(), &saddr.sin6_addr);

   memcpy(&mreq.ipv6mr_multiaddr, &saddr.sin6_addr, sizeof(mreq.ipv6mr_multiaddr));
   mreq.ipv6mr_interface = ifidx;

   if (setsockopt(sd, IPPROTO_IPV6, IPV6_JOIN_GROUP, (char*)&mreq, sizeof(mreq)))
   {
      perror("setsockopt");
      return 1;
   }

   while (true)
   {
      len = sendto(sd, buf, strlen(buf), 0, (const struct sockaddr*)&saddr, sizeof(saddr));
      if (len < 0)
      {
         perror("sendto");
         return 1;
      }

      printf("Sent: %s\n", buf);

#ifdef _WIN32
      Sleep(delay_secs * 1000); // Windows Sleep is milliseconds
#else
      sleep(delay_secs); // Unix sleep is seconds
#endif
   }

   closesocket(sd);

#ifdef _WIN32
   WSACleanup();
#endif

   return 0;
}
