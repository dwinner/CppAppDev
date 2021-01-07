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

      MManBackendLauncher(const MManBackendLauncher& other)
         : ipv6Host_(other.ipv6Host_),
           udpPort_(other.udpPort_),
           tcpPort_(other.tcpPort_),
           forceStop_(false)
      {
         udpMulticastThrPtr_ = nullptr;
         tcpServerThrPtr_ = nullptr;
      }

      MManBackendLauncher(MManBackendLauncher&& other) noexcept
         : ipv6Host_(std::move(other.ipv6Host_)),
           udpPort_(other.udpPort_),
           tcpPort_(other.tcpPort_),
           forceStop_(false)
      {
         other.udpMulticastThrPtr_ = nullptr;
         other.tcpServerThrPtr_ = nullptr;
         delete &other;

         udpMulticastThrPtr_ = nullptr;
         tcpServerThrPtr_ = nullptr;
      }

      MManBackendLauncher& operator=(const MManBackendLauncher& other)
      {
         if (this == &other)
         {
            return *this;
         }

         ipv6Host_ = other.ipv6Host_;
         udpPort_ = other.udpPort_;
         tcpPort_ = other.tcpPort_;
         forceStop_ = false;

         delete tcpServerThrPtr_;
         delete udpMulticastThrPtr_;
         udpMulticastThrPtr_ = nullptr;
         tcpServerThrPtr_ = nullptr;

         return *this;
      }

      MManBackendLauncher& operator=(MManBackendLauncher&& other) noexcept
      {
         if (this == &other)
         {
            return *this;
         }

         ipv6Host_ = std::move(other.ipv6Host_);
         udpPort_ = other.udpPort_;
         tcpPort_ = other.tcpPort_;
         forceStop_ = false;

         other.udpMulticastThrPtr_ = nullptr;
         other.tcpServerThrPtr_ = nullptr;
         delete &other;

         udpMulticastThrPtr_ = nullptr;
         tcpServerThrPtr_ = nullptr;

         return *this;
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
