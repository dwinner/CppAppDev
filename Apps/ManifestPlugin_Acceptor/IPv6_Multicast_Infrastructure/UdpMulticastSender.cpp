#include "pch.h"
#include "UdpMulticastSender.h"

namespace ipv6_multicast
{
   int UdpMulticastSender::CreateSocket()
   {
      using namespace std;

      const int socketDesc = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
      if (socketDesc < 0)
      {
#ifdef _DEBUG
         perror("socket creation failure");
#endif
         exit(EXIT_FAILURE);
      }

      return socketDesc;
   }

   void UdpMulticastSender::ConfigureSocket(const int socketDesc)
   {
      int on = 1;
      if (setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof on))
      {
#ifdef _DEBUG
         perror("setsockopt");
#endif
         exit(EXIT_FAILURE);
      }

      int ifidx = 0;
      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_IF, reinterpret_cast<const char*>(&ifidx), sizeof(ifidx)))
      {
#ifdef _DEBUG
         perror("setsockopt");
#endif
         exit(EXIT_FAILURE);
      }

      int hops = 255;
      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, reinterpret_cast<const char*>(&hops), sizeof(hops)))
      {
#ifdef _DEBUG
         perror("setsockopt");
#endif
         exit(EXIT_FAILURE);
      }

      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, reinterpret_cast<const char*>(&on), sizeof(on)))
      {
#ifdef _DEBUG
         perror("setsockopt");
#endif
         exit(EXIT_FAILURE);
      }
   }

   sockaddr_in6 UdpMulticastSender::ConfigureSocketAddress(const int port, const string& host, const int socketDesc)
   {
      struct sockaddr_in6 saddr{};

      memset(&saddr, 0, sizeof(struct sockaddr_in6));
      saddr.sin6_family = AF_INET6;
      saddr.sin6_port = htons(port);
      inet_pton(AF_INET6, host.c_str(), &saddr.sin6_addr);

      struct ipv6_mreq mreq{};
      memcpy(&mreq.ipv6mr_multiaddr, &saddr.sin6_addr, sizeof mreq.ipv6mr_multiaddr);
      const auto ifidx = 0;
      mreq.ipv6mr_interface = ifidx;

      if (setsockopt(socketDesc, IPPROTO_IPV6, IPV6_JOIN_GROUP, reinterpret_cast<char*>(&mreq), sizeof mreq))
      {
#ifdef _DEBUG
         perror("setsockopt");
#endif

         exit(EXIT_FAILURE);
      }

      return saddr;
   }

   bool UdpMulticastSender::InternalExchange(const int socketDesc, const sockaddr_in6& sockAddr)
   {
      const int delaySec = 1;

      using namespace mman;
      const char* buffer = ManifestMulticastMsg;
      const int bufferLen = ManifestMulticastMsgLength;

      while (true)
      {
         const ssize_t sentLen = sendto(socketDesc, buffer, bufferLen, 0,
                                        reinterpret_cast<const struct sockaddr*>(&sockAddr),
                                        sizeof sockAddr);
         if (sentLen < 0)
         {
#ifdef _DEBUG
            perror("sendto");
#endif
            return false;
         }

#ifdef _DEBUG
         cout << "Sent: " << sentLen << endl;
#endif

#ifdef _WIN32
         Sleep(delaySec * 1000); // Windows Sleep in milliseconds
#else
         sleep(delaySec); // Unix sleep is seconds
#endif
      }
   }
}
