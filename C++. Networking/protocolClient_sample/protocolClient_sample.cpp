/**
 * Simple client for exchange via some protocol
 */

#include "stdafx.h"
#include "Socket.h"
#include <cassert>
#include <iostream>
#include <type_traits>

#ifndef NDEBUG
#include <sstream>
#endif

using namespace std;

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>

#define UsingWinsock 1

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

   string address("");
   string port("3000");
   Socket mySocket(address, port);
   int connectionResult{mySocket.Connect()};

   if (connectionResult != -1)
   {
      stringstream output{"QUESTION"};
      mySocket.Send(move(output));

      stringstream input{mySocket.Receive()};
      if (input.rdbuf()->in_avail() > 0)
      {
         string question;
         getline(input, question, '\0');
         input.clear();

         while (question != "FINISHED")
         {
            cout << question << endl;

            string answer;
            cin >> answer;

            output << "ANSWER ";
            output << answer;
            mySocket.Send(move(output));
            input = mySocket.Receive();
            if (input.rdbuf()->in_avail() == 0)
            {
               break;
            }

            string result;
            getline(input, result, '\0');
            cout << result << endl;
            output << "QUESTION";
            mySocket.Send(move(output));

            input = mySocket.Receive();
            getline(input, question, '\0');
            input.clear();
         }
      }
   }

   return 0;
}
