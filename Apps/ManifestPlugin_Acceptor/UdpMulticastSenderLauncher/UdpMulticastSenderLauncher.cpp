#include <cstdlib>
#include "framework.h"
#include "UdpMulticastSender.h"

/**
 * Additional include directories: $(SolutionDir)include_dir
 * Additional library directories: $(SolutionDir)Debug
 * Additional dependencies: $(OutputPath)lib_name.lib
 */

int main()
{
   const auto defaultUdpPort = 1900;

   using namespace multicast;
   using namespace mman;

   UdpMulticastSender udpMulticastSender(defaultUdpPort);
   const auto result = udpMulticastSender.Exchange(ManifestMulticastMsg, ManifestMulticastMsgLength);

   if (result == false)
   {
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
