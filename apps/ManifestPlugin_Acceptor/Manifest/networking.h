#pragma once
#include <vector>

namespace manifest_client
{
   void throw_if_error(int ret, const char* sErr);

   void throw_error(const char* sErr);

   std::vector<CString> read_manifest(const char* sAddr, u_short udpPort, u_short tcpPort);
}
