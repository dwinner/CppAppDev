#pragma once

#include <string>
#include <utility>
#include "WinsockWrapper.h"

namespace multicast
{
   using namespace std;

   const string DefaultLoopbackIPv6Host = "ff02::1:5";

   class IPv6MulticastBase
   {
      int _port;
      string _host;

   protected:
      virtual int CreateSocket() = 0;
      virtual void ConfigureSocket(int socketDesc) = 0;
      virtual sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) = 0;
      virtual bool InternalExchange(const char* buffer, int bufferLen, int delaySec, bool endless, int socketDesc,
                                    const sockaddr_in6& sockAddr) = 0;

   public:
      virtual ~IPv6MulticastBase() = default;

      explicit IPv6MulticastBase(const int port, string host = DefaultLoopbackIPv6Host)
         : _port(port),
           _host(move(host))
      {
      }

      IPv6MulticastBase(const IPv6MulticastBase& other) = default;

      IPv6MulticastBase(IPv6MulticastBase&& other) noexcept = default;

      IPv6MulticastBase& operator=(const IPv6MulticastBase& other) = default;

      IPv6MulticastBase& operator=(IPv6MulticastBase&& other) noexcept = default;

      int GetPort() const
      {
         return _port;
      }

      void SetPort(const int port)
      {
         _port = port;
      }

      string GetHost() const
      {
         return _host;
      }

      void SetHost(const string& host)
      {
         _host = host;
      }

      bool Exchange(const char* buffer, int bufferLen, int delaySec = 1, bool endless = true);
   };
}
