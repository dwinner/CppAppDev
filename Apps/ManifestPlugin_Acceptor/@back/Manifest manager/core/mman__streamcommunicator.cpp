/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__streamcommunicator.cpp
*
* Description  : Manifest manager, stream communicator implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#include "ethil__integrity.h" /* Fix warnings about undefined preprocessing identifiers */
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mman_ce.h"
#include "mman_ci.h"
#include "mman__streamcommunicator.hpp"
#include "mman__errorhandler.hpp"

namespace manifest_manager
{
    StreamCommunicator::StreamCommunicator(int32 i32SocketHandle):
        i32TCPSocketFD(MMAN_GENERIC_SOCKET_ERROR)
    {
        this->i32TCPSocketFD = i32SocketHandle;
    }
	
	StreamCommunicator::~StreamCommunicator(void)
    {
        if ((i32TCPSocketFD != MMAN_GENERIC_SOCKET_ERROR))
        {
            vDisconnect();
        }
    }
	
	void StreamCommunicator::vDisconnect(void)
    {
        if (i32TCPSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            // Shut down read / write operations on the socket
            (void)shutdown(i32TCPSocketFD, SHUT_RDWR);

            // Destroy the socket
            (void)close(i32TCPSocketFD);
            i32TCPSocketFD = MMAN_GENERIC_SOCKET_ERROR;
        }
    }

    ssize_t StreamCommunicator::xWrite(const uint8 *pu8buffer, size_t xBufferSize)
    {
        ssize_t xNumWritten = MMAN_OK;

        if (i32TCPSocketFD == MMAN_GENERIC_SOCKET_ERROR)
        {
            MMAN__mReportError(ErrorHandler::nenInvalidSocketFileDescriptor, 0);

            xNumWritten = MMAN_GENERIC_SOCKET_ERROR;
        }
        if (pu8buffer == NULL)
        {
            MMAN__mReportError(ErrorHandler::nenNullPointer, 0);

            xNumWritten =  MMAN_GENERIC_SOCKET_ERROR;
        }

        if (xNumWritten != MMAN_GENERIC_SOCKET_ERROR)
        {
            xNumWritten = send(i32TCPSocketFD, pu8buffer, xBufferSize, 0);
        }

        return xNumWritten;
    }

    ssize_t StreamCommunicator::xRead(uint8 *pu8buffer, size_t xBufferSize) const
    {
        ssize_t xNumRead = MMAN_OK;

        if (i32TCPSocketFD == MMAN_GENERIC_SOCKET_ERROR)
        {
            MMAN__mReportError(ErrorHandler::nenInvalidSocketFileDescriptor, 0);

            xNumRead = MMAN_GENERIC_SOCKET_ERROR;
        }
        if (pu8buffer == NULL)
        {
            MMAN__mReportError(ErrorHandler::nenNullPointer, 0);

            xNumRead = MMAN_GENERIC_SOCKET_ERROR;
        }

        if (xNumRead != MMAN_GENERIC_SOCKET_ERROR)
        {
            xNumRead = recv(i32TCPSocketFD, pu8buffer, xBufferSize, 0);
        }

        return xNumRead;
    }

    int32 StreamCommunicator::i32Poll(int32 i32Timeout) const
    {
        const nfds_t xSockets = MMAN__nNumberOfTCPSockets; // number of sockets
        struct pollfd stPollFD;
        stPollFD.fd = i32TCPSocketFD;
        stPollFD.events = POLLIN;

        return poll(&stPollFD, xSockets, i32Timeout);
    }
}