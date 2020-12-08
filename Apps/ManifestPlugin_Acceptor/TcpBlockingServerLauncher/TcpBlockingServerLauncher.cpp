#include <iostream>
#include <cstdlib>
#include "TcpBlockingServer.h"

int main()
{
   using namespace ipv6_multicast;

   TcpBlockingServer tcpBlockingSrv;
   const bool result = tcpBlockingSrv.Exchange();
   if (result == false)
   {
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
