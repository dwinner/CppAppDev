/**
 * IPv6 multi cast example - sender
 */

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

const int DelaySecs = 1;
const int DefaultPort = 1900;
const std::string DefaultHost = "ff02::1:5";

void init_wsa();

void clean_wsa();

int create_socket();

void configure_socket(int socketDesc);

sockaddr_in6 configure_socket_address(int port, int socketDesc);

void broadcast_data(int socketDesc, sockaddr_in6 sockAddr, const char* buffer, int bufferLen);

#define MSGBUFSIZE   1400

int _tmain()
{
   init_wsa();
   const int socketDesc = create_socket();
   configure_socket(socketDesc);
   const struct sockaddr_in6 saddr = configure_socket_address(DefaultPort, socketDesc);
   const char* buf = mman::ManifestBroadcastMsg;
   broadcast_data(socketDesc, saddr, buf, MANIFEST_BROADCAST_MSG_LENGTH);
   closesocket(socketDesc);
   clean_wsa();

   return 0;
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

void clean_wsa()
{
#ifdef _WIN32
   WSACleanup();
#endif
}

int create_socket()
{
   using namespace std;

   const int socketDesc = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
   if (socketDesc < 0)
   {
#ifdef _DEBUG
      perror("socket creation failure");
#endif
      exit(EXIT_FAILURE);
   }

   return socketDesc;
}

void configure_socket(const int socketDesc)
{
   int on = 1;
   if (setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof on))
   {
#ifdef _DEBUG
      perror("setsockopt");
#endif

      exit(EXIT_FAILURE);
   }

   int ifidx = 0;
   if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_IF, reinterpret_cast<const char*>(&ifidx), sizeof(ifidx)))
   {
#ifdef _DEBUG
      perror("setsockopt");
#endif

      exit(EXIT_FAILURE);
   }

   int hops = 255;
   if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, reinterpret_cast<const char*>(&hops), sizeof(hops)))
   {
#ifdef _DEBUG
      perror("setsockopt");
#endif

      exit(EXIT_FAILURE);
   }

   if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, reinterpret_cast<const char*>(&on), sizeof(on)))
   {
#ifdef _DEBUG
      perror("setsockopt");
#endif

      exit(EXIT_FAILURE);
   }
}

sockaddr_in6 configure_socket_address(const int port, int socketDesc)
{
   struct sockaddr_in6 saddr{};

   memset(&saddr, 0, sizeof(struct sockaddr_in6));
   saddr.sin6_family = AF_INET6;
   saddr.sin6_port = htons(port);
   inet_pton(AF_INET6, hostAddr.c_str(), &saddr.sin6_addr);

   struct ipv6_mreq mreq{};
   memcpy(&mreq.ipv6mr_multiaddr, &saddr.sin6_addr, sizeof(mreq.ipv6mr_multiaddr));
   const int ifidx = 0;
   mreq.ipv6mr_interface = ifidx;

   if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_JOIN_GROUP, reinterpret_cast<char*>(&mreq), sizeof(mreq)))
   {
#ifdef _DEBUG
      perror("setsockopt");
#endif

      exit(EXIT_FAILURE);
   }

   return saddr;
}

void broadcast_data(const int socketDesc, sockaddr_in6 sockAddr, const char* buffer, const int bufferLen)
{
   ssize_t len = 1;

   while (true)
   {
      len = sendto(socketDesc, buffer, bufferLen, 0, reinterpret_cast<const struct sockaddr*>(&sockAddr),
                   sizeof sockAddr);
      if (len < 0)
      {
         perror("sendto");
         break;
      }

      printf("Sent: %ld bytes\n", len);

#ifdef _WIN32
      Sleep(DelaySecs * 1000); // Windows Sleep in milliseconds
#else
		sleep(delay_secs); // Unix sleep is seconds
#endif
   }
}
