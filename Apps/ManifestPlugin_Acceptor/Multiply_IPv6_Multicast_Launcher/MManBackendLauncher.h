#pragma once
#include <atomic>
#include <string>
#include <thread>
#include <utility>

namespace ipv6_multicast
{
   class MManBackendLauncher final
   {
   public:
      MManBackendLauncher(std::string ipv6Host, const int udpPort, const int tcpPort)
         : ipv6Host_(std::move(ipv6Host)),
           udpPort_(udpPort),
           tcpPort_(tcpPort),
           forceStop_(false)
      {
      }

      void Start();

      void Stop();

   private:
      std::string ipv6Host_;
      int udpPort_;
      int tcpPort_;
      std::atomic_bool forceStop_;
      std::thread tcpServerThr_;
      std::thread udpMulticastThr_;

      void LaunchTcpServer();

      void LaunchUdpMulticast();

      void QuitRequest();
   };
}
