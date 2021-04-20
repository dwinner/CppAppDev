/**
 * Reading the manifest
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

static const std::string Ipv6Host = "ff02::1:5";
static const int UdpPort = 1900;
static const int TcpPort = 1991;

// The one and only application object
CWinApp the_app;

int main()
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
         auto manifestVector = manifest_client::read_manifest(Ipv6Host.c_str(), UdpPort, TcpPort);
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
