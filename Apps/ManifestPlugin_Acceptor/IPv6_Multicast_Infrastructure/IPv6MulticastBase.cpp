#include "pch.h"
#include "IPv6MulticastBase.h"

namespace multicast
{   
   bool IPv6MulticastBase::Exchange(const char* buffer, const int bufferLen, const int delaySec, const bool endless)
   {
      WinsockWrapper winsock;

      const auto socketDesc = CreateSocket();
      ConfigureSocket(socketDesc);
      const auto sockAddr = ConfigureSocketAddress(_port, _host, socketDesc);
      const auto result = InternalExchange(buffer, bufferLen, delaySec, endless, socketDesc, sockAddr);
      closesocket(socketDesc);

      return result;
   }
}
