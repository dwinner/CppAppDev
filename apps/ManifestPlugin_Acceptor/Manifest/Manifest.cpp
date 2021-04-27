/**
 * Reading the manifest:
 * MMan_Client -host=ff08::1:5 -udpport=19000 -tcpport=19001
 */

#include "pch.h"
#include "framework.h"
#include "Manifest.h"
#include <iostream>
#include <vector>
#include "CBase64.h"
#include "ManifestProvisioning.pb.h"
#include "networking.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::tuple<std::string, int, int> parse_args(int argc, char* argv[]);

// The one and only application object
CWinApp the_app;

int main(int argc, char* argv[])
{
   int nRetCode = 0;
   auto* hModule = ::GetModuleHandle(nullptr);

   if (hModule != nullptr)
   {
      // initialize MFC and print and error on failure
      if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
      {
         wprintf(L"Fatal Error: MFC initialization failed\n");
         nRetCode = 1;
      }
      else
      {
         std::vector<CString> manifestVector;

         try
         {
            std::string ipv6Host;
            u_short udpPort;
            u_short tcpPort;
            std::tie(ipv6Host, udpPort, tcpPort) = parse_args(argc, argv);

            manifestVector = manifest_client::read_manifest(ipv6Host.c_str(), udpPort, tcpPort);
         }
         catch (std::runtime_error &ex)
         {
            std::cerr << ex.what();
            return EXIT_FAILURE;
         }

         CString completeManifest;

         for (auto& manifest : manifestVector)
         {
            CBase64 base64;
            const auto decodeSize = base64.CalculateRecquiredDecodeOutputBufferSize(manifest);

            CString sManifestDecoded;
            auto* pBuffer = sManifestDecoded.GetBuffer(static_cast<int>(decodeSize + 1));
            base64.DecodeBuffer(manifest, pBuffer);
            sManifestDecoded.ReleaseBuffer();
            if (!completeManifest.IsEmpty())
            {
               completeManifest += "\n";
            }

            completeManifest += sManifestDecoded;
         }

         // output the received manifest in json format
         std::cout << completeManifest << std::endl;

         nRetCode = 0;
      }
   }
   else
   {
      wprintf(L"Fatal Error: GetModuleHandle failed\n");
      nRetCode = 1;
   }

   return nRetCode;
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
   if (posOfEqual != std::string::npos && posOfEqual < hostArg.length())
   {
      std::string hostKey = hostArg.substr(0, posOfEqual);
      hostValue = hostArg.substr(posOfEqual + 1, hostArg.length());
   }

   posOfEqual = udpPortArg.find(equalChar);
   if (posOfEqual != std::string::npos && posOfEqual < udpPortArg.length())
   {
      std::string udpKey = udpPortArg.substr(0, posOfEqual);
      udpPortValue = udpPortArg.substr(posOfEqual + 1, udpPortArg.length());
   }

   posOfEqual = tcpPortArg.find(equalChar);
   if (posOfEqual != std::string::npos && posOfEqual < tcpPortArg.length())
   {
      std::string tcpKey = tcpPortArg.substr(0, posOfEqual);
      tcpPortValue = tcpPortArg.substr(posOfEqual + 1, tcpPortArg.length());
   }

   return std::make_tuple(hostValue, std::stoi(udpPortValue), std::stoi(tcpPortValue));
}
