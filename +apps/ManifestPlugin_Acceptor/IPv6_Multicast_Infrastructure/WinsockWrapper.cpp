#include "pch.h"
#include "WinsockWrapper.h"

WinsockWrapper::WinsockWrapper()
{
#ifdef USING_WINSOCK
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
   {
      exit(EXIT_FAILURE);
   }

#ifndef NDEBUG
   cout << "Winsock started!" << endl;
#endif
#endif
}

WinsockWrapper::~WinsockWrapper()
{
#if USING_WINSOCK
   WSACleanup();
#ifndef NDEBUG
   cout << "Winsock shut down!" << endl;
#endif
#endif
}
