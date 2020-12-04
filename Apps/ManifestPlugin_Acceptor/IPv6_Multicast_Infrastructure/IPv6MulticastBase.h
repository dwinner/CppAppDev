#pragma once

#include <string>
#include <utility>
#include "WinsockWrapper.h"

namespace ipv6_multicast
{
   using namespace std;

   const string DefaultLoopbackIPv6Host = "ff02::1:5";
   const int DefaultUdpPort = 1900;
   const int DefaultTcpPort = 1991;

   class Ipv6MulticastBase
   {
   public:
      virtual ~Ipv6MulticastBase() = default;

      explicit Ipv6MulticastBase(const int port, string host = DefaultLoopbackIPv6Host)
         : _port(port),
           _host(move(host))
      {
      }

      bool Exchange();

   protected:
      virtual int CreateSocket() = 0;

      virtual void ConfigureSocket(int socketDesc) = 0;

      virtual sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) = 0;

      virtual bool InternalExchange(int socketDesc, const sockaddr_in6& sockAddr) = 0;

   private:
      int _port;
      string _host;
   };
}
