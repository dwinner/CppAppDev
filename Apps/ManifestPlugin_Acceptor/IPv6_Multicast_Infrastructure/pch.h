#ifndef PCH_H
#define PCH_H

#include "framework.h"
#ifdef _WIN32

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>

#pragma comment (lib, "Ws2_32.lib")
using ssize_t = SSIZE_T;

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#endif

#endif //PCH_H
