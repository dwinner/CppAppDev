#include "pch.h"
#include "IPv6MulticastBase.h"

namespace ipv6_multicast
{
   bool Ipv6MulticastBase::Exchange(const bool stop) const
   {
      WinsockWrapper winsock;

      const auto socketDesc = CreateSocket();
      ConfigureSocket(socketDesc);
      const auto sockAddr = ConfigureSocketAddress(port_, host_, socketDesc);
      const auto result = InternalExchange(socketDesc, sockAddr, stop);
      closesocket(socketDesc);

      return result;
   }
}
