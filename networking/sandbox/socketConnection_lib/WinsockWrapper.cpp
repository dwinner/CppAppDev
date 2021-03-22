#include "WinsockWrapper.h"

WinsockWrapper::WinsockWrapper()
{
#ifdef UsingWinsock
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
#if UsingWinsock
   WSACleanup();
#ifndef NDEBUG
   cout << "Winsock shut down!" << endl;
#endif
#endif
}
