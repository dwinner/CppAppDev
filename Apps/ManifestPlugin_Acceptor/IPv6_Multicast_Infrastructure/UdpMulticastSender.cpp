#include "pch.h"
#include "UdpMulticastSender.h"
//#include <netioapi.h>
#include <thread>

namespace ipv6_multicast
{
   int UdpMulticastSender::CreateSocket() const
   {
      using namespace std;

      const int socketDesc = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
      if (socketDesc < 0)
      {
         trace("socket creation failure");
         exit(EXIT_FAILURE);
      }

      return socketDesc;
   }

   void UdpMulticastSender::ConfigureSocket(const int socketDesc) const
   {
      int reuseAddr = 1;
      if (setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuseAddr), sizeof reuseAddr))
      {
         trace("setsockopt failure");
         exit(EXIT_FAILURE);
      }
      
      /*int ifindex = 16;
      ifindex = if_nametoindex("ethernet_7");
      int result = setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_IF, reinterpret_cast<const char*>(&ifindex), sizeof ifindex);*/

      int ifIdx = 0;
      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_IF, reinterpret_cast<const char*>(&ifIdx), sizeof ifIdx))
      {
         trace("setsockopt failure");
         exit(EXIT_FAILURE);
      }

      int hops = 255;
      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, reinterpret_cast<const char*>(&hops), sizeof hops))
      {
         trace("setsockopt failure");
         exit(EXIT_FAILURE);
      }

      int loop = 0;
      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, reinterpret_cast<const char*>(&loop), sizeof loop))
      {
         trace("setsockopt failure");
         exit(EXIT_FAILURE);
      }
   }

   sockaddr_in6 UdpMulticastSender::ConfigureSocketAddress(const int port, const string& host,
                                                           const int socketDesc) const
   {
      struct sockaddr_in6 saddr{};

      memset(&saddr, 0, sizeof(struct sockaddr_in6));
      saddr.sin6_family = AF_INET6;
      saddr.sin6_port = htons(static_cast<u_short>(port));
      inet_pton(AF_INET6, host.c_str(), &saddr.sin6_addr);

      struct ipv6_mreq mreq{};
      memcpy(&mreq.ipv6mr_multiaddr, &saddr.sin6_addr, sizeof mreq.ipv6mr_multiaddr);
      const auto ifidx = 0;
      mreq.ipv6mr_interface = ifidx;

      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_JOIN_GROUP, reinterpret_cast<char*>(&mreq), sizeof mreq))
      {
         trace("setsockopt failure");
         exit(EXIT_FAILURE);
      }

      return saddr;
   }

   bool UdpMulticastSender::InternalExchange(const int socketDesc, const sockaddr_in6& sockAddr,
                                             std::atomic_bool& stop) const
   {
      using namespace mman;
      const char* buffer = ManifestMulticastMsg;
      const int bufferLen = ManifestMulticastMsgLength;

      while (!stop)
      {
         const int delaySec = 1;
         const ssize_t sentLen = sendto(socketDesc, buffer, bufferLen, 0,
                                        reinterpret_cast<const struct sockaddr*>(&sockAddr), sizeof sockAddr);
         if (sentLen < 0)
         {
            trace("sendto failure");
            return false;
         }

         trace("Sent: " + std::to_string(sentLen));
         std::this_thread::sleep_for(std::chrono::seconds(delaySec));
      }

      return true;
   }
}
