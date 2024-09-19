#include "MManBackendLauncher.h"
#include "UdpMulticastSender.h"

using namespace ipv6_multicast;

int main()
{
   const string ipv6Host = "ff02::1:5";
   const int udpPort = 1900;
   const int tcpPort = 1991;

   auto* backendLauncherPtr = new MManBackendLauncher(ipv6Host, udpPort, tcpPort);
   backendLauncherPtr->Start();   

   std::cout << "Press enter to quit";
   std::cin.get();   

   backendLauncherPtr->Stop();
   delete backendLauncherPtr;

   return 0;
}
