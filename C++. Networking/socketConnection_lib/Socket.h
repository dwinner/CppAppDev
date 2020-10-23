#pragma once

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "WinsockWrapper.h"

using namespace std;

/**
 * \brief Socket wrapper class
 */
class Socket
{
private:
#if !USING_WINSOCK
   using SOCKET = int;
#endif

   addrinfo* _serverInfo{nullptr};
   SOCKET _socket{static_cast<SOCKET>(0xFFFFFFFF)};
   sockaddr_storage _acceptedSocketStorage{};
   socklen_t _acceptedSocketSize{sizeof _acceptedSocketStorage};

   void CreateSocket(string& webAddress, string& port, addrinfo& hints)
   {
      getaddrinfo(webAddress.c_str(), port.c_str(), &hints, &_serverInfo);
      _socket = socket(_serverInfo->ai_family, _serverInfo->ai_socktype, _serverInfo->ai_protocol);
   }

   Socket(int newSocket, sockaddr_storage&& socketStorage)
      : _socket{newSocket},
        _acceptedSocketStorage(move(socketStorage))
   {
   }

public:
   Socket(string& port)
   {
#ifndef NDEBUG
      stringstream portStream{port};
      int portValue{};
      portStream >> portValue;
      assert(portValue > 1024); // Ports under 1024 are reserved for certain applications and protocols!
#endif

      addrinfo hints{};
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;

      string address{""};
      CreateSocket(address, port, hints);
   }

   Socket(string& webAddress, string& port)
   {
      addrinfo hints{};
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;

      CreateSocket(webAddress, port, hints);
   }

   Socket(string& webAddress, string& port, addrinfo& hints)
   {
      CreateSocket(webAddress, port, hints);
   }

   ~Socket()
   {
      Close();
   }

   bool IsValid()
   {
      return _socket != -1;
   }

   int Connect()
   {
      int connectionResult{connect(_socket, _serverInfo->ai_addr, _serverInfo->ai_addrlen)};

#ifndef NDEBUG
      cout << (connectionResult == -1 ? "Connection failed!" : "Connection successful!") << endl;
#endif

      return connectionResult;
   }

   int Bind()
   {
      int bindResult{::bind(_socket, _serverInfo->ai_addr, _serverInfo->ai_addrlen)};

#ifndef NDEBUG
      cout << (bindResult == -1 ? "Bind Failed!" : "Bind Successful") << endl;
#endif

      return bindResult;
   }

   int Listen(const int queueSize) const
   {
      const int listenResult{listen(_socket, queueSize)};

#ifndef NDEBUG
      cout << (listenResult == -1 ? "Listen Failed" : "Listen Succeeded") << endl;
#endif

      return listenResult;
   }

   Socket Accept()
   {
      const SOCKET newSocket{accept(_socket, reinterpret_cast<sockaddr*>(&_acceptedSocketStorage), &_acceptedSocketSize)};

#ifndef NDEBUG
      cout << (newSocket == -1 ? "Accept Failed" : "Accept Succeeded") << endl;
#endif

      _acceptedSocketSize = sizeof(_acceptedSocketStorage);
      return Socket(newSocket, move(_acceptedSocketStorage));
   }

   void Close()
   {
#ifdef _MSC_VER
      closesocket(_socket);
#else
      close(_socket);
#endif

      _socket = -1;
      freeaddrinfo(_serverInfo);
   }

   ssize_t Send(const stringstream data) const
   {
      const string packetData{data.str()};
      const ssize_t sendResult{send(_socket, packetData.c_str(), packetData.length(), 0)};

#ifndef NDEBUG
      cout << (sendResult == -1 ? "Send Failed" : "Send Succeeded") << endl;
#endif

      return sendResult;
   }

   stringstream Receive()
   {
      const int size{1024};
      char dataReceived[size];

      const ssize_t receiveResult{recv(_socket, dataReceived, size, 0)};

#ifndef NDEBUG
      if (receiveResult == -1)
      {
         cout << "Receive Failed" << endl;
      }
      else if (receiveResult == 0)
      {
         cout << "Receive Detected Closed Connection!" << endl;
         Close();
      }
      else
      {
         dataReceived[receiveResult] = '\0';
         cout << "Receive Succeeded" << endl;
      }
#endif
      stringstream data{dataReceived};

      return move(data);
   }
};
