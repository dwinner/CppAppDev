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
         udpMulticastThrPtr_ = nullptr;
         tcpServerThrPtr_ = nullptr;         
      }

      void Start();      

      void Stop();

      ~MManBackendLauncher();

   private:
      std::string ipv6Host_;
      int udpPort_;
      int tcpPort_;
      std::atomic_bool forceStop_;
      std::thread* udpMulticastThrPtr_;
      std::thread* tcpServerThrPtr_;      

      void LaunchTcpServer();

      void LaunchUdpMulticast();

      void QuitRequest();
   };
}
