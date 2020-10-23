#pragma once

#include <iostream>

using namespace std;

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>

#define USING_WINSOCK 1

using ssize_t = SSIZE_T;

#else

#define UsingWinsock 0

#endif

class WinsockWrapper
{
public:
   WinsockWrapper();

   ~WinsockWrapper();
};
