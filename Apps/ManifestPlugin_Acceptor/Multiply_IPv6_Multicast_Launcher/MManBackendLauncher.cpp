#include "MManBackendLauncher.h"
#include "TcpBlockingServer.h"
#include "UdpMulticastSender.h"

namespace ipv6_multicast
{
   using namespace std;

   void MManBackendLauncher::Start()
   {
      udpMulticastThrPtr_ = new thread(&MManBackendLauncher::LaunchTcpServer, this);
      this_thread::sleep_for(1s);
      tcpServerThrPtr_ = new thread(&MManBackendLauncher::LaunchUdpMulticast, this);
      this_thread::sleep_for(1s);
   }

   void MManBackendLauncher::Stop()
   {
      thread quitThr{&MManBackendLauncher::QuitRequest, this};
      quitThr.join();
      udpMulticastThrPtr_->join();
      tcpServerThrPtr_->join();
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

   MManBackendLauncher::~MManBackendLauncher()
   {
      delete udpMulticastThrPtr_;
      delete tcpServerThrPtr_;
      udpMulticastThrPtr_ = nullptr;
      tcpServerThrPtr_ = nullptr;
   }
}
