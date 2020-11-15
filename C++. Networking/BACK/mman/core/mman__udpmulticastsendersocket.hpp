/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__udpmulticastsendersocket.hpp
*
* Description  : Manifest manager, internal interface, UDP multicast sender socket
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent.
****************************************************************************/

#ifndef MMAN__UDPMULTICASTSENDERSOCKET_HPP_
#define MMAN__UDPMULTICASTSENDERSOCKET_HPP_

#include "ethil__integrity.h" /* Fix warnings about undefined preprocessing identifiers */
#include <netinet/in.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

namespace manifest_manager
{
    class UdpMulticastSenderSocket
    {
    public:
        /**
        * @brief UDP multicast socket constructor.
        * @param[in] u16PortNumber Used port number
        */
        explicit UdpMulticastSenderSocket(uint16 u16PortNumber);

        /**
        * @brief UDP multicast socket destructor.
        */
        ~UdpMulticastSenderSocket(void);

        /**
        * @brief Close multicast sender socket.
        */
        void vClose(void);

        /**
        * @brief Send data over UDP multicast socket.
        * @param[in] pu8MulticastMessage Buffer containing a message
        * @param[in] xMessageLen Length of a message being sent
        * @return Length in bytes of a message sent or MMAN_GENERIC_SOCKET_ERROR.
        */
        ssize_t xSend(const uint8 *const pu8MulticastMessage, size_t xMessageLen);

    private:
        /**
        * @brief UdpMulticastSenderSocket copy constructor.
        * @param[in, out] UdpMulticastSenderSocket Reference to UdpMulticastSenderSocket
        */
        UdpMulticastSenderSocket(const UdpMulticastSenderSocket&);

        /**
        * @brief UdpMulticastSenderSocket assignment operator.
        * @param[in, out] UdpMulticastSenderSocket Reference to UdpMulticastSenderSocket
        */
        UdpMulticastSenderSocket& operator=(const UdpMulticastSenderSocket&);

        /**
        * UDP multicast socket filer descriptor.
        */
        int32 i32MulticastSocketFD;

        /**
        * Socket address structure for multicast.
        */
        sockaddr_in6 stMulticastAddress;
    };
}

#endif /* MMAN__UDPMULTICASTSENDERSOCKET_HPP_ */

