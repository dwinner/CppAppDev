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

#if !UsingWinsock
   using SOCKET = int;
#endif

   addrinfo* m_ServerInfo{nullptr};
   SOCKET m_Socket{static_cast<SOCKET>(0xFFFFFFFF)};
   sockaddr_storage m_AcceptedSocketStorage{};
   socklen_t m_AcceptedSocketSize{sizeof(m_AcceptedSocketStorage)};

   void CreateSocket(string& webAddress, string& port, addrinfo& hints);

   Socket(int newSocket, sockaddr_storage&& socketStorage);

public:

   Socket(string& port);

   Socket(string& webAddress, string& port);

   Socket(string& webAddress, string& port, addrinfo& hints);

   Socket(const Socket& other) = delete;

   Socket(Socket&& other) :
      m_ServerInfo(other.m_ServerInfo),
      m_Socket(other.m_Socket),
      m_AcceptedSocketStorage(other.m_AcceptedSocketStorage),
      m_AcceptedSocketSize(other.m_AcceptedSocketSize)
   {
      if (this != &other)
      {
         other.m_ServerInfo = nullptr;
         other.m_Socket = -1;
         other.m_AcceptedSocketStorage = sockaddr_storage{};
         other.m_AcceptedSocketSize = sizeof(other.m_AcceptedSocketSize);
      }
   }

   ~Socket();

   bool IsValid();

   int Connect();

   int Bind();

   int Listen(int queueSize);

   Socket Accept();

   void Close();

   ssize_t Send(stringstream data);

   stringstream Receive();
};
