/**
 * Simple server for exchange via some protocol
 */

#include <array>
#include <cassert>
#include <future>
#include <iostream>
#include <thread>
#include <type_traits>
#include <vector>
#include "Socket.h"
#include "stdafx.h"

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

namespace
{
   const int NUM_QUESTIONS{ 2 };

   const array<string, NUM_QUESTIONS> QUESTIONS =
   {
      "What is the capital of Australia?",
      "What is the capital of the USA?"
   };

   const array<string, NUM_QUESTIONS> ANSWERS =
   {
      "Canberra",
      "Washington DC"
   };
}

bool ProtocolThread(reference_wrapper<Socket> connectionSocketRef);

int _tmain(int argc, _TCHAR* argv[])
{
   WinsockWrapper myWinsockWrapper;
   string port("3000");
   Socket myListeningSocket(port);
   int bindResult{ myListeningSocket.Bind() };

   assert(bindResult != -1);

   if (bindResult != -1)
   {
      int listenResult{ myListeningSocket.Listen(5) };
      assert(listenResult != -1);

      if (listenResult != -1)
      {
         while (true)
         {
            Socket acceptedSocket{ myListeningSocket.Accept() };
            async(launch::async, ProtocolThread, ref(acceptedSocket));
         }
      }
   }

   return 0;
}

bool ProtocolThread(reference_wrapper<Socket> connectionSocketRef)
{
   Socket socket{ move(connectionSocketRef.get()) };
   int currentQuestion{ 0 };
   string message;

   while (message != "QUIT")
   {
      stringstream sstream{ socket.Receive() };
      if (sstream.rdbuf()->in_avail() == 0)
      {
         break;
      }
      sstream >> message;
      stringstream output;
      if (message == "QUESTION")
      {
         if (currentQuestion >= NUM_QUESTIONS)
         {
            output << "FINISHED";
            socket.Send(move(output));
            cout << "Quiz Complete!" << endl;
            break;
         }
         output << QUESTIONS[currentQuestion];
      }
      else if (message == "ANSWER")
      {
         string answer;
         sstream >> answer;
         if (answer == ANSWERS[currentQuestion])
         {
            output << "You are correct!";
         }
         else
         {
            output << "Sorry the correct answer is " << ANSWERS[currentQuestion];
         }
         ++currentQuestion;
      }
      socket.Send(move(output));
   }

   return true;
}
