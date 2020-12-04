#include <cstdlib>
#include "UdpMulticastSender.h"

int main()
{
   using namespace ipv6_multicast;

   UdpMulticastSender udpMulticastSender;
   const auto result = udpMulticastSender.Exchange();
   if (result == false)
   {
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
