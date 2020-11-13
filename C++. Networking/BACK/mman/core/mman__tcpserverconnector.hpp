/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__tcpserverconnector.hpp
*
* Description  : Manifest manager, internal interface, TCP server connector
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent.
****************************************************************************/

#ifndef MMAN__TCPSERVERCONNECTOR_HPP_
#define MMAN__TCPSERVERCONNECTOR_HPP_

#include <netinet/in.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

#include "mman__streamcommunicator.hpp"

namespace manifest_manager
{
    class TcpServerConnector
    {
    public:
        /**
        * @brief TCP server connector constructor.
        * @param[in] u16TCPServerPort TCP server port
        */
        explicit TcpServerConnector(uint16 u16TCPServerPort);

        /**
        * @brief TCP server connector destructor.
        */
        ~TcpServerConnector(void);

        /**
        * @brief Tries to establish a TCP connection.
        * @return StreamCommunicator if there is a connection.
        */
        StreamCommunicator *poEstablishConnection(void) const;

        /**
        * @brief Close TCP connection.
        */
        void vCloseConnection(void);

    private:
        /**
        * @brief TcpServerConnector copy constructor.
        * @param[in, out] TcpServerConnector Reference to TcpServerConnector
        */
        TcpServerConnector(const TcpServerConnector&);

        /**
        * @brief TcpServerConnector assignment operator.
        * @param[in, out] TcpServerConnector Reference to TcpServerConnector
        */
        TcpServerConnector& operator=(const TcpServerConnector&);

        /**
        * TCP socket descriptor.
        */
        int32 i32TCPSocketFD;

        /**
        * Server address holder.
        */
        sockaddr_in6 stServerAddress;
    };
}

#endif /* MMAN__TCPSERVERCONNECTOR_HPP_ */

