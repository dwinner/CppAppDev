#include <cstdlib>
#include <thread>
#include "TcpBlockingServer.h"
#include "UdpMulticastSender.h"

using namespace std;
using namespace ipv6_multicast;

void launch_tcp_blocking_server();
void launch_udp_multicast_sender();

int main()
{
   thread mmanUdpServerThread{launch_udp_multicast_sender};
   thread mmanTcpBlockingThread{launch_tcp_blocking_server};   

   mmanUdpServerThread.join();
   mmanTcpBlockingThread.join();

   return 0;
}

void launch_tcp_blocking_server()
{
   const TcpBlockingServer tcpBlockingSrv;
   const auto result = tcpBlockingSrv.Exchange();
   if (result == false)
   {
      exit(EXIT_FAILURE);
   }
}

void launch_udp_multicast_sender()
{
   const UdpMulticastSender udpMulticastSender;
   const auto result = udpMulticastSender.Exchange();
   if (result == false)
   {
      exit(EXIT_FAILURE);
   }
}
