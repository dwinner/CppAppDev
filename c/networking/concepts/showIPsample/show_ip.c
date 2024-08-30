/**
 * show_ip.c -- show IP addresses for a host given on the command line
 * showIPsample www.example.net
 */

#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif

#include <stdio.h>

const char* host = "www.example.net";

int main()
{
#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return 1;
   }
#endif

   struct addrinfo hints, *res, *p;
   int status;
   char ipstr[INET6_ADDRSTRLEN];   

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
   hints.ai_socktype = SOCK_STREAM;

   if ((status = getaddrinfo(host, NULL, &hints, &res)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerrorA(status));
      return 2;
   }

   printf("IP addresses for %s:\n\n", host);

   for (p = res; p != NULL; p = p->ai_next)
   {
      void* addr;
      char* ipVersion;

      // get the pointer to the address itself,
      // different fields in IPv4 and IPv6:
      if (p->ai_family == AF_INET) // IPv4
      {
         struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
         addr = &(ipv4->sin_addr);
         ipVersion = "IPv4";
      }
      else // IPv6
      {
         struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
         addr = &(ipv6->sin6_addr);
         ipVersion = "IPv6";
      }

      // convert the IP to a string and print it:
      inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
      printf("  %s: %s\n", ipVersion, ipstr);
   }

   freeaddrinfo(res); // free the linked list

#if defined(_WIN32)
   WSACleanup();
#endif

   return 0;
}
