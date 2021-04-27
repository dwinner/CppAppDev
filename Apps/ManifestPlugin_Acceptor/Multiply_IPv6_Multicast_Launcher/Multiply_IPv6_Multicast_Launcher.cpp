/**
 * Usage: IPv6_Multicast -host=ff08::1:5 -udpport=19000 -tcpport=19001
 */

#include "MManBackendLauncher.h"
#include "UdpMulticastSender.h"

using namespace ipv6_multicast;

std::tuple<std::string, int, int> parse_args(int args, char* argv[]);

int main(int argc, char* argv[])
{
   std::string ipv6Host;
   int udpPort;
   int tcpPort;
   std::tie(ipv6Host, udpPort, tcpPort) = parse_args(argc, argv);

   auto* backendLauncherPtr = new MManBackendLauncher(ipv6Host, udpPort, tcpPort);
   backendLauncherPtr->Start();

   std::cout << "Press enter to quit";
   std::cin.get();

   backendLauncherPtr->Stop();
   delete backendLauncherPtr;

   return 0;
}

std::tuple<std::string, int, int> parse_args(int argc, char* argv[])
{
   if (argc != 4)
   {
      std::cerr << "IPv6_Multicast -host=host_name -udpport=udp_port -tcpport=tcp_port";
      exit(EXIT_FAILURE);
   }

   const std::string hostArg(argv[1]);
   const std::string udpPortArg(argv[2]);
   const std::string tcpPortArg(argv[3]);

   std::string hostValue;
   std::string udpPortValue;
   std::string tcpPortValue;

   const char equalChar = '=';

   size_t posOfEqual = hostArg.find(equalChar);
   if (posOfEqual != string::npos && posOfEqual < hostArg.length())
   {
      std::string hostKey = hostArg.substr(0, posOfEqual);
      hostValue = hostArg.substr(posOfEqual + 1, hostArg.length());
   }

   posOfEqual = udpPortArg.find(equalChar);
   if (posOfEqual != string::npos && posOfEqual < udpPortArg.length())
   {
      std::string udpKey = udpPortArg.substr(0, posOfEqual);
      udpPortValue = udpPortArg.substr(posOfEqual + 1, udpPortArg.length());
   }

   posOfEqual = tcpPortArg.find(equalChar);
   if (posOfEqual != string::npos && posOfEqual < tcpPortArg.length())
   {
      std::string tcpKey = tcpPortArg.substr(0, posOfEqual);
      tcpPortValue = tcpPortArg.substr(posOfEqual + 1, tcpPortArg.length());
   }

   return std::make_tuple(hostValue, std::stoi(udpPortValue), std::stoi(tcpPortValue));
}
