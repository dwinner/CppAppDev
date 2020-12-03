#pragma once

#include <cstdlib>
#include "IPv6MulticastBase.h"

namespace multicast
{
   class UdpMulticastSender final : public IPv6MulticastBase
   {
   public:
      explicit UdpMulticastSender(const int port)
         : IPv6MulticastBase(port)
      {
      }

      UdpMulticastSender(const int port, const string& host)
         : IPv6MulticastBase(port, host)
      {
      }

      explicit UdpMulticastSender(const IPv6MulticastBase& other)
         : IPv6MulticastBase(other)
      {
      }

      explicit UdpMulticastSender(IPv6MulticastBase&& other)
         : IPv6MulticastBase(other)
      {
      }

   protected:
      int CreateSocket() override;

      void ConfigureSocket(int socketDesc) override;

      sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) override;

      bool InternalExchange(const char* buffer, int bufferLen, int delaySec, bool endless, int socketDesc,
                            const sockaddr_in6& sockAddr) override;

   public:
      ~UdpMulticastSender() = default;
   };
}
