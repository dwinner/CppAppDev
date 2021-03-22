/**
 * Creating a Program That Can Receive Data
 */

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <vector>

#include "Socket.h"

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
#include <sys/socket.h>
#include <unistd.h>

#define UsingWinsock 0

#endif


int _tmain(int argc, _TCHAR* argv[])
{
   WinsockWrapper myWinsockWrapper;

   string port{"3000"};   
   Socket myBindingSocket(port);
   myBindingSocket.Bind();

   const int listenResult{myBindingSocket.Listen(5)};
   assert(listenResult != -1);

   Socket acceptResult{myBindingSocket.Accept()};
   assert(acceptResult.IsValid());

   stringstream data{acceptResult.Receive()};

   string message;
   getline(data, message, '\0');

   cout << "Received Message: " << message << endl;

   return 0;
}
