#include "stdafx.h"

#ifdef _WIN32

#include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
#include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MSGBUFSIZE   256

const int DefaultPort = 1900;
const std::string DefaultHost = "239.192.100.1";

int _tmain()
{   
   const char* group = DefaultHost.c_str();  // e.g. 239.255.255.250 for SSDP
   const int port = DefaultPort;             // 0 if error, which is an invalid port

#ifdef _WIN32
   //
   // Initialize Windows Socket API with given VERSION.
   //
   WSADATA wsaData;
   if (WSAStartup(0x0101, &wsaData))
   {
      perror("WSAStartup");
      return 1;
   }
#endif

   // create what looks like an ordinary UDP socket
   //
   int fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (fd < 0)
   {
      perror("socket");
      return 1;
   }

   // allow multiple sockets to use the same PORT number
   //
   u_int yes = 1;
   int setSockResult = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
   if (setSockResult < 0)
   {
      perror("Reusing ADDR failed");
      return 1;
   }

   // set up destination address
   //
   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY); // differs from sender
   addr.sin_port = htons(port);

   // bind to receive address
   //
   if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
   {
      perror("bind");
      return 1;
   }

   // use setsockopt() to request that the kernel join a multicast group
   //
   struct ip_mreq mreq;
   mreq.imr_multiaddr.s_addr = inet_addr(group);
   mreq.imr_interface.s_addr = htonl(INADDR_ANY);
   setSockResult = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
   if (setSockResult < 0)
   {
      perror("setsockopt");
      return 1;
   }

   // now just enter a read-print loop
   //
   while (true)
   {
      char msgbuf[MSGBUFSIZE];
      int addrlen = sizeof(addr);
      int nbytes = recvfrom(fd, msgbuf, MSGBUFSIZE, 0, (struct sockaddr*)&addr, &addrlen);
      if (nbytes < 0)
      {
         perror("recvfrom");
         return 1;
      }

      msgbuf[nbytes] = '\0';
      puts(msgbuf);
   }

#ifdef _WIN32
   //
   // Program never actually gets here due to infinite loop that has to be
   // canceled, but since people on the internet wind up using examples
   // they find at random in their own code it's good to show what shutting
   // down cleanly would look like.
   //
   WSACleanup();
#endif

   return 0;
}
