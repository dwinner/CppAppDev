/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__tcpserverconnector.cpp
*
* Description  : Manifest manager, TCP server connector implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#include "ethil__integrity.h" /* Fix warnings about undefined preprocessing identifiers */
#include <unistd.h>

#include "mman_ce.h"
#include "mman_ci.h"
#include "mman__tcpserverconnector.hpp"
#include "mman__errorhandler.hpp"

namespace manifest_manager
{
    TcpServerConnector::TcpServerConnector(uint16 u16TCPServerPort):
        i32TCPSocketFD(MMAN_GENERIC_SOCKET_ERROR),
        stServerAddress()
    {
        int32 i32Result;
        int32 i32On = 1;
        int32 i32TcpHopLimit = 255;

        i32TCPSocketFD = socket(AF_INET6, SOCK_STREAM, 0);

        if (i32TCPSocketFD == MMAN_GENERIC_SOCKET_ERROR)
        {
            MMAN__mReportError(ErrorHandler::nenInvalidSocketFileDescriptor, 0);
        }

        // Construct server address
        (void)memset(&stServerAddress, 0, sizeof(struct sockaddr_in6));
        stServerAddress.sin6_family = AF_INET6;
        stServerAddress.sin6_port = htons(u16TCPServerPort);
        stServerAddress.sin6_addr = in6addr_any;

        // Allow socket descriptor to be reuseable
        i32Result = setsockopt(i32TCPSocketFD, SOL_SOCKET, SO_REUSEADDR, (char *)&i32On, sizeof(i32On));
        if (i32Result < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionReuseAddrFailure, errno);
        }

        i32Result = setsockopt(i32TCPSocketFD, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &i32TcpHopLimit, sizeof(i32TcpHopLimit));
        if (i32Result < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionIPv6UnicastHopLimitFailure, errno);
        }

        // Bind specified port number to a local enpoint's address
        i32Result = bind(i32TCPSocketFD, (struct sockaddr *)&stServerAddress, sizeof(struct sockaddr_in6));
        if (i32Result < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketBindFailure, errno);
        }

        i32Result = listen(i32TCPSocketFD, MMAN__nTCPSocketBacklogSize);
        if (i32Result < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketListenFailure, errno);
        }
    }

    TcpServerConnector::~TcpServerConnector(void)
    {
        if (i32TCPSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            vCloseConnection();
        }        
    }

    StreamCommunicator *TcpServerConnector::poEstablishConnection(void) const
    {
        StreamCommunicator *poCommunicator = NULL;
        fd_set xReadFds;
        bool boDataRead = false;

        FD_ZERO(&xReadFds);
        FD_SET(i32TCPSocketFD, &xReadFds);

        timeval stTimeout = { 0 };
        stTimeout.tv_usec = MMAN__nSocketSelectTimeout;

        if (i32TCPSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            if (select(i32TCPSocketFD + 1, &xReadFds, NULL, NULL, &stTimeout) > 0)
            {
                // Try accept
                int32 i32SocketHandle = accept(i32TCPSocketFD, NULL, NULL);
                if (i32SocketHandle >= 0)
                {
                    // In case of successfull acceptance, create a TCP communicator object
                    poCommunicator = new StreamCommunicator(i32SocketHandle);
                }
            }
        }

        return poCommunicator;
    }

    void TcpServerConnector::vCloseConnection(void)
    {
        if (i32TCPSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            // Shut down read / write operations on the socket
            int32 i32Result = shutdown(i32TCPSocketFD, SHUT_RDWR);
            if (i32Result < 0)
            {
                MMAN__mReportError(ErrorHandler::nenSocketShutdownFailure, errno);
            }

            // Destroy the socket
            (void)close(i32TCPSocketFD);
            i32TCPSocketFD = MMAN_GENERIC_SOCKET_ERROR;
        }
    }
}