#include "pch.h"
#include "networking.h"
#include "Guard.h"
#include "ManifestProvisioning.pb.h"

namespace manifest_client
{
   std::vector<CString> read_manifest(const char* sAddr, u_short udpPort, u_short tcpPort)
   {
      std::vector<BYTE> manifest;
      WSADATA wsaData;
      WSAStartup(MAKEWORD(2, 2), &wsaData);

      int returnValue = 0;

      // create what looks like an ordinary UDP socket
      int fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
      throw_error(fd, "Init udp socket");

      manifest_reader::Guard socketGuard([&] { if (fd > 0) closesocket(fd); });

      // set up destination address
      sockaddr_in6 addr{};
      addr.sin6_family = AF_INET6;
      addr.sin6_port = htons(udpPort);

      // bind to receive address
      int bindResult = bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof addr);
      throw_error(bindResult, "Calling bind failed");

      // Join membership
      ipv6_mreq group{};
      group.ipv6mr_interface = 0;
      inet_pton(AF_INET6, sAddr, &group.ipv6mr_multiaddr);
      int setOptResult = setsockopt(fd, IPPROTO_IPV6, IPV6_JOIN_GROUP, reinterpret_cast<char*>(&group), sizeof group);
      throw_error(setOptResult, "Call setsockopt failed");

      // Wait for UDP frame for 5 seconds.
      fd_set rset;
      FD_ZERO(&rset);
      FD_SET(fd, &rset);
      timeval timeout = { 5, 0 };
      returnValue = select(0, &rset, nullptr, nullptr, &timeout);
      throw_error(returnValue, "Calling select failed");
      if (returnValue == 0)
      {
         throw_error("No UDP frame received");
      }

      u_char rxData[1600]; // Buffer to receive udp broadcast
      sockaddr_in6 from{};
      int fromlen = sizeof from;
      int rxLen = recvfrom(fd, reinterpret_cast<char*>(rxData), sizeof rxData, 0, reinterpret_cast<sockaddr*>(&from), &fromlen);

      closesocket(fd);

      manifest_manager_msg::MM_CollectionVersionAnnounce annouce;
      if (!annouce.ParseFromArray(rxData, rxLen))
      {
         throw_error("Invalid manifest announce received");
      }

      auto sCollectionVersion = annouce.collectionversion();

      // Create TCP socket to receive manifest data, packed in google protobuf
      fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
      throw_error(fd, "Init tcp socket failed");
      from.sin6_port = htons(tcpPort);
      throw_error(connect(fd, reinterpret_cast<sockaddr*>(&from), fromlen), "Calling connect failed");

      manifest_manager_msg::MM_ClientRequest_V1 clientRequest;
      clientRequest.set_collectionversion(sCollectionVersion);
      auto sClientRequest = clientRequest.SerializeAsString();
      int sendResult = send(fd, sClientRequest.c_str(), sClientRequest.length(), 0);
      throw_error(sendResult, "Calling send failed");

      // shutdown the connection since no more data will be sent
      throw_error(shutdown(fd, SD_SEND), "Calling shutdown failed");

      rxLen = 0;
      do
      {
         rxLen = recv(fd, reinterpret_cast<char*>(rxData), sizeof rxData, 0);
         throw_error(rxLen, "Calling tcp recv failed");
         auto pos = manifest.size();
         manifest.resize(manifest.size() + rxLen);
         for (int nByte = 0; nByte < rxLen; ++nByte)
         {
            manifest[pos + nByte] = rxData[nByte];
         }
      } while (rxLen > 0);

      if (manifest.empty())
      {
         throw_error("No manifest received");
      }

      manifest_manager_msg::MM_ManifestCollection_V1 manifestCollection;
      if (!manifestCollection.ParseFromArray(manifest.data(), manifest.size()))
      {
         throw_error("Invalid manifest received");
      }

      std::vector<CString> manifestVector;
      for (int nManifest = 0; nManifest < manifestCollection.manifests_size(); ++nManifest)
      {
         auto val = manifestCollection.manifests(nManifest).c_str();
         CString cStr(val);
         manifestVector.push_back(cStr);
      }

      if (manifestVector.empty())
      {
         throw_error("No manifest received");
      }

      return manifestVector;
   }

   void throw_error(const int ret, const char* sErr)
   {
      if (ret < 0)
      {
         printf("Error: %s ret=%d err=%d", sErr, ret, WSAGetLastError());
         throw_error(sErr);
      }
   }

   void throw_error(const char* sErr)
   {
      throw std::runtime_error(sErr);
   }
}
