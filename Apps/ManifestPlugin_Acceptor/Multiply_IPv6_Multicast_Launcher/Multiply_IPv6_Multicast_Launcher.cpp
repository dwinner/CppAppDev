#include <atomic>
#include <cstdlib>
#include <thread>
#include "TcpBlockingServer.h"
#include "UdpMulticastSender.h"

using namespace ipv6_multicast;

atomic_bool force_stop(false);

void launch_tcp_blocking_server(std::atomic_bool& stop);
void launch_udp_multicast_sender(std::atomic_bool& stop);
void stop_listening(std::atomic_bool& stop);

int main()
{
   thread mmanUdpServerThread{launch_udp_multicast_sender, std::ref(force_stop)};
   this_thread::sleep_for(2s);
   thread mmanTcpBlockingThread{launch_tcp_blocking_server, std::ref(force_stop)};
   this_thread::sleep_for(1s);
   thread quitThr{ stop_listening, std::ref(force_stop) };

   mmanUdpServerThread.join();
   mmanTcpBlockingThread.join();
   quitThr.join();

   return 0;
}

void launch_tcp_blocking_server(std::atomic_bool& stop)
{
   const TcpBlockingServer tcpBlockingServer;
   const auto result = tcpBlockingServer.Exchange(stop);
   if (result == false)
   {
      exit(EXIT_FAILURE);
   }
}

void launch_udp_multicast_sender(std::atomic_bool& stop)
{
   const UdpMulticastSender udpMulticastSender;
   const auto result = udpMulticastSender.Exchange(stop);
   if (result == false)
   {
      exit(EXIT_FAILURE);
   }
}

void stop_listening(std::atomic_bool& stop)
{
   std::cout << "Press enter to quit";
   std::cin.get();
   stop = true;
}
