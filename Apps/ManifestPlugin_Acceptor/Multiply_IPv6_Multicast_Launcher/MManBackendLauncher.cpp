#include "MManBackendLauncher.h"
#include "TcpBlockingServer.h"
#include "UdpMulticastSender.h"

namespace ipv6_multicast
{
   using namespace std;

   void MManBackendLauncher::Start()
   {
      udpMulticastThr_ = thread(&MManBackendLauncher::LaunchTcpServer, this);
      this_thread::sleep_for(1s);
      tcpServerThr_ = thread(&MManBackendLauncher::LaunchUdpMulticast, this);
      this_thread::sleep_for(1s);
   }

   void MManBackendLauncher::Stop()
   {
      std::thread quitThr{&MManBackendLauncher::QuitRequest, this};
      quitThr.join();
      udpMulticastThr_.join();
      tcpServerThr_.join();
   }

   void MManBackendLauncher::LaunchTcpServer()
   {
      const TcpBlockingServer tcpBlockingServer(tcpPort_, ipv6Host_);
      tcpBlockingServer.Exchange(ref(forceStop_));
   }

   void MManBackendLauncher::LaunchUdpMulticast()
   {
      const UdpMulticastSender udpMulticastSender(udpPort_, ipv6Host_);
      udpMulticastSender.Exchange(ref(forceStop_));
   }

   void MManBackendLauncher::QuitRequest()
   {
      forceStop_ = true;
   }
}
