#pragma once
#include "IPv6MulticastBase.h"

namespace ipv6_multicast
{
   class TcpBlockingServer final : public Ipv6MulticastBase
   {
   public:
      explicit TcpBlockingServer()
         : Ipv6MulticastBase(DefaultTcpPort)
      {
      }

      explicit TcpBlockingServer(const int port)
         : Ipv6MulticastBase(port)
      {
      }

      TcpBlockingServer(int port, const string& host)
         : Ipv6MulticastBase(port, host)
      {
      }

   protected:
      int CreateSocket() const override;

      void ConfigureSocket(int socketDesc) const override;

      sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) const override;

      bool InternalExchange(int socketDesc, const sockaddr_in6& sockAddr) const override;

   private:
      static string TruncateResponse(char* buffer, int bufferLen, int messageLen);
   };
}
