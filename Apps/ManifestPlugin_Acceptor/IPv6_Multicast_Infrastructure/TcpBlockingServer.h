#pragma once
#include "IPv6MulticastBase.h"

namespace ipv6_multicast
{
   enum class select_status
   {
      select_error,
      not_in_set,
      timeout,
      has_accepted_client
   };

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

      TcpBlockingServer(const int port, const string& host)
         : Ipv6MulticastBase(port, host)
      {
      }

   protected:
      int CreateSocket() const override;

      void ConfigureSocket(int socketDesc) const override;

      sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) const override;

      bool InternalExchange(int socketDesc, const sockaddr_in6& sockAddr, std::atomic_bool& stop) const override;

   private:
      static select_status GetMultiplexingStatus(int socketDesc, long seconds, long microseconds);

      static string TruncateResponse(char* buffer, int bufferLen, int messageLen);
   };
}
