#pragma once

#include <atomic>
#include <string>
#include <utility>
#include "WinsockWrapper.h"

namespace ipv6_multicast
{
   const string DefaultLoopbackIPv6Host = "ff02::1:5";
   const int DefaultUdpPort = 1900;
   const int DefaultTcpPort = 1991;

   inline void trace(const std::string& aMessage)
   {
#ifdef _DEBUG
      std::cout << aMessage << std::endl;
#endif
   }

   class Ipv6MulticastBase
   {
   public:
      Ipv6MulticastBase(const Ipv6MulticastBase& other) = default;

      Ipv6MulticastBase(Ipv6MulticastBase&& other) noexcept = default;

      Ipv6MulticastBase& operator=(const Ipv6MulticastBase& other) = default;

      Ipv6MulticastBase& operator=(Ipv6MulticastBase&& other) noexcept = default;

      virtual ~Ipv6MulticastBase() = default;

      explicit Ipv6MulticastBase(const int port, string host = DefaultLoopbackIPv6Host)
         : port_(port),
           host_(std::move(host))
      {
      }
      
      bool Exchange(std::atomic_bool& stop) const;

   protected:
      virtual int CreateSocket() const = 0;

      virtual void ConfigureSocket(int socketDesc) const = 0;

      virtual sockaddr_in6 ConfigureSocketAddress(int port, const string& host, int socketDesc) const = 0;

      virtual bool InternalExchange(int socketDesc, const sockaddr_in6& sockAddr, std::atomic_bool& stop) const = 0;

   private:
      int port_;
      string host_;
   };
}
