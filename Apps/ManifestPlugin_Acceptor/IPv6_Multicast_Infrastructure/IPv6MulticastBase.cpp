#include "pch.h"
#include "Ipv6MulticastBase.h"

namespace ipv6_multicast
{
   bool Ipv6MulticastBase::Exchange()
   {
      WinsockWrapper winsock;

      const auto socketDesc = CreateSocket();
      ConfigureSocket(socketDesc);
      const auto sockAddr = ConfigureSocketAddress(_port, _host, socketDesc);
      const auto result = InternalExchange(socketDesc, sockAddr);
      closesocket(socketDesc);

      return result;
   }
}
