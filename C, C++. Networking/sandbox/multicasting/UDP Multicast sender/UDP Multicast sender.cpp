// UDP multicast sender.cpp : Defines the entry point for the console application.
//

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
#include <unistd.h> // for sleep()

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

const int DefaultPort = 1900;
const std::string DefaultHost = "239.192.100.1";

int _tmain()
{
   const char* group = DefaultHost.c_str();  // e.g. 239.255.255.250 for SSDP
   int port = DefaultPort;                   // 0 if error, which is an invalid port

   // !!! If test requires, make these configurable via args
   //
   const int delay_secs = 1;
   const char* message = "Hello, multicast!";

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

   // set up destination address
   //
   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = inet_addr(group);
   addr.sin_port = htons(port);

   // now just sendto() our destination!
   //
   while (true)
   {
      char ch = 0;
      int nbytes = sendto(fd, message, strlen(message), 0, (struct sockaddr*)&addr, sizeof(addr));
      if (nbytes < 0)
      {
         perror("sendto");
         return 1;
      }

#ifdef _WIN32
      Sleep(delay_secs * 1000); // Windows Sleep is milliseconds
#else
      sleep(delay_secs); // Unix sleep is seconds
#endif
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
