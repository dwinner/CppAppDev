/**
 * The simple client program
 */

#include "stdafx.h"
#include <type_traits>

#ifndef NDEBUG
#include <sstream>
#endif

using namespace std;

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>

#define USING_WINSOCK 1

using ssize_t = SSIZE_T;

#else

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>#define UsingWinsock 0

#endif#include "WinsockWrapper.h"
#include "Socket.h"


int _tmain(int argc, _TCHAR* argv[])
{
   WinsockWrapper myWinsockWrapper;

   string port("3000");
   string address{ "192.168.222.57" };
   Socket myConnectingSocket(address, port);
   myConnectingSocket.Connect();

   const string message("Sending Data Over a Network!");
   stringstream data;
   data << message;

   myConnectingSocket.Send(move(data));

   return 0;
}

