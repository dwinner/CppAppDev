#pragma once

#include "IPv6MulticastBase.h"

namespace ipv6_multicast
{
   class UdpMulticastSender final : public Ipv6MulticastBase
   {
   public:
      explicit UdpMulticastSender()
         : Ipv6MulticastBase(DefaultUdpPort)
      {
      }

      explicit UdpMulticastSender(const int port)
         : Ipv6MulticastBase(port)
      {
      }

      UdpMulticastSender(const int port, const string& host)
         : Ipv6MulticastBase(port, host)
      {
      }

   protected:
      int CreateSocket() override;

      void ConfigureSocket(int socketDesc) override;

      sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) override;

      bool InternalExchange(int socketDesc, const sockaddr_in6& sockAddr) override;
   };
}
