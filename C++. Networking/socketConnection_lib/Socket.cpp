#include "Socket.h"

void Socket::CreateSocket(string& webAddress, string& port, addrinfo& hints)
{
   getaddrinfo(webAddress.c_str(), port.c_str(), &hints, &m_ServerInfo);
   m_Socket = socket(m_ServerInfo->ai_family, m_ServerInfo->ai_socktype, m_ServerInfo->ai_protocol);

   assert(m_Socket != INVALID_SOCKET);
}

Socket::Socket(int newSocket, sockaddr_storage&& socketStorage)
   : m_Socket{newSocket},
     m_AcceptedSocketStorage(move(socketStorage))
{
}

Socket::Socket(string& port)
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

Socket::Socket(string& webAddress, string& port)
{
   addrinfo hints{};
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   CreateSocket(webAddress, port, hints);
}

Socket::Socket(string& webAddress, string& port, addrinfo& hints)
{
   CreateSocket(webAddress, port, hints);
}

Socket::~Socket()
{
   Close();
}

bool Socket::IsValid()
{
   return m_Socket != -1;
}

int Socket::Connect()
{
   int connectionResult{connect(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen)};

#ifndef NDEBUG
   cout << (connectionResult == -1 ? "Connection failed!" : "Connection successful!") << endl;
#endif

   return connectionResult;
}

int Socket::Bind()
{
   int bindResult{bind(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen)};

#ifndef NDEBUG
   cout << (bindResult == -1 ? "Bind Failed!" : "Bind Successful") << endl;
#endif

   return bindResult;
}

int Socket::Listen(int queueSize)
{
   int listenResult{listen(m_Socket, queueSize)};

#ifndef NDEBUG
   cout << (listenResult == -1 ? "Listen Failed" : "Listen Succeeded") << endl;
#endif

   return listenResult;
}

Socket Socket::Accept()
{
   SOCKET socketFd = accept(m_Socket, reinterpret_cast<sockaddr*>(&m_AcceptedSocketStorage), &m_AcceptedSocketSize);
   SOCKET newSocket{socketFd};

#ifndef NDEBUG
   cout << (newSocket == -1 ? "Accept Failed" : "Accept Succeeded") << endl;
#endif

   m_AcceptedSocketSize = sizeof(m_AcceptedSocketStorage);

   return Socket(newSocket, move(m_AcceptedSocketStorage));
}

void Socket::Close()
{
#ifdef _MSC_VER
   closesocket(m_Socket);
#else
   close(m_Socket);
#endif

   m_Socket = -1;
   freeaddrinfo(m_ServerInfo);
}

ssize_t Socket::Send(stringstream data)
{
   string packetData{data.str()};
   ssize_t sendResult{send(m_Socket, packetData.c_str(), packetData.length(), 0)};

#ifndef NDEBUG
   cout << (sendResult == -1 ? "Send Failed" : "Send Succeeded") << endl;
#endif

   return sendResult;
}

stringstream Socket::Receive()
{
   const int size{1024};
   char dataReceived[size];
   int memorySize = size * sizeof(char);
   ssize_t receiveResult{recv(m_Socket, dataReceived, memorySize, 0)};

#ifndef NDEBUG
   if (receiveResult == -1)
   {
      cout << "Receive Failed" << endl;

#if UsingWinsock
      cout << "The error code is: " << WSAGetLastError() << '\n';
#endif
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
