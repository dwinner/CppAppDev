/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__udpmulticastsendersocket.cpp
*
* Description  : Manifest manager, UDP multicast sender socket
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#include "ethil__integrity.h" /* Fix warnings about undefined preprocessing identifiers */
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

#if !defined(_LOCAL) && !defined(_WIN32)
#include "ethsrv_ce.h"
#endif

#include "mman_ce.h"
#include "mman_ci.h"
#include "mman__ethernet.hpp"
#include "mman__udpmulticastsendersocket.hpp"
#include "mman__errorhandler.hpp"

namespace manifest_manager
{
    UdpMulticastSenderSocket::UdpMulticastSenderSocket(uint16 u16PortNumber):
        i32MulticastSocketFD(MMAN_GENERIC_SOCKET_ERROR),
        stMulticastAddress()
    {
        int32 i32On = 1; 
        int32 i32Off = 0;
        int32 i32MaxHops = 255;
        int32 i32IfIndex = if_nametoindex(ETHIL_VLAN_IFNAME);

        i32MulticastSocketFD = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

        if (i32MulticastSocketFD == MMAN_GENERIC_SOCKET_ERROR)
        {
            MMAN__mReportError(ErrorHandler::nenInvalidSocketFileDescriptor, 0);
        }

        // Allow socket address re-usage
        if (setsockopt(i32MulticastSocketFD, SOL_SOCKET, SO_REUSEADDR, static_cast<int32*>(&i32On), sizeof(i32On)) < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionReuseAddrFailure, errno);
            (void)close(i32MulticastSocketFD);
        }

        // Set source address
        memset(&stMulticastAddress, 0, sizeof(stMulticastAddress));
        stMulticastAddress.sin6_family = AF_INET6;
        stMulticastAddress.sin6_port = htons(u16PortNumber);
        stMulticastAddress.sin6_scope_id = i32IfIndex;
        stMulticastAddress.sin6_addr = in6addr_any;

        // Bind specified port number to a local enpoint's address
        if (bind(i32MulticastSocketFD, reinterpret_cast<struct sockaddr*>(&stMulticastAddress), sizeof(stMulticastAddress)) < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketBindFailure, errno);
            (void)close(i32MulticastSocketFD);
        }

        // Set Ethernet interface the data will be sent through
        if (setsockopt(i32MulticastSocketFD, IPPROTO_IPV6, IPV6_MULTICAST_IF, static_cast<int32*>(&i32IfIndex), sizeof(i32IfIndex)) < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionIPv6MulticastIFFailure, errno);
        }

        // Disable loopbacks to avoid receiving own datagrams
        if (setsockopt(i32MulticastSocketFD, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, static_cast<int32*>(&i32Off), sizeof(i32Off)) < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionIPv6MulticastLoopFailure, errno);
            (void)close(i32MulticastSocketFD);
        }

        // Restrict amount of hops before discarding a packet
        if (setsockopt(i32MulticastSocketFD, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, static_cast<int32*>(&i32MaxHops), sizeof(i32MaxHops)) < 0)
        {
            MMAN__mReportError(ErrorHandler::nenSocketOptionIPv6MulticastHopsFailure, errno);
        }

        // After bind port number to a local endpoint, reuse the socket for sending data.
        // Not going to receive any data on multicast socket, 
        // so specify the remote endpoint's address for further send operations
        memcpy(&stMulticastAddress.sin6_addr, &MMAN__au8RemoteEndpointMulticastAddress, MMAN_nEndpointAddressLenght);
    }

    UdpMulticastSenderSocket::~UdpMulticastSenderSocket(void)
    {        
        if (i32MulticastSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            vClose();
        }
    }

    void UdpMulticastSenderSocket::vClose(void)
    {
        if (i32MulticastSocketFD != MMAN_GENERIC_SOCKET_ERROR)
        {
            // Destroy the socket
            (void)close(i32MulticastSocketFD);
            i32MulticastSocketFD = MMAN_GENERIC_SOCKET_ERROR;
        }
    }

    ssize_t UdpMulticastSenderSocket::xSend(const uint8 *const pu8MulticastMessage, size_t xMessageLen)
    {
        ssize_t xBytesSent = 0;

        if (pu8MulticastMessage == NULL)
        {
            xBytesSent = static_cast<ssize_t>(MMAN_GENERIC_SOCKET_ERROR);
        }

        if (xBytesSent != MMAN_GENERIC_SOCKET_ERROR)
        {
            xBytesSent = sendto(
                i32MulticastSocketFD,
                pu8MulticastMessage,
                xMessageLen,
                0,
                reinterpret_cast<struct sockaddr*>(&stMulticastAddress),
                sizeof(stMulticastAddress));
        }

        return xBytesSent;
    }
}