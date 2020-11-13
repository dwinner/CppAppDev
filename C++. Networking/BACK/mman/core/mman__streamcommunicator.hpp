/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__streamcommunicator.hpp
*
* Description  : Manifest manager, internal interface, stream communicator
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#ifndef MMAN__STREAMCOMMUNICATOR_HPP_
#define MMAN__STREAMCOMMUNICATOR_HPP_

#include <sys/types.h>

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
    class StreamCommunicator
    {
    public:
        /**
        * @brief Stream communicator constructor.
        * @param[in] i32SocketHandle Socket descriptor
        */
        explicit StreamCommunicator(int32 i32SocketHandle);
		
		/**
        * @brief Stream communicator destructor.
        * @param[in] i32SocketHandle Socket descriptor
        */
        ~StreamCommunicator(void);
		
		/**
        * @brief Close TCP socket.
        */
        void vDisconnect(void);

        /**
        * @brief Write byte stream into the socket.
        * @param[in] pu8buffer Write buffer
        * @param[in] xBufferSize Write buffer size
        * @return Number of bytes written or MMAN_GENERIC_SOCKET_ERROR.
        */
        ssize_t xWrite(const uint8 *pu8buffer, size_t xBufferSize);

        /**
        * @brief Read byte stream from the TCP socket.
        * @param[in] pu8buffer Read buffer
        * @param[in] xBufferSize Read buffer size
        * @return Number of bytes read or MMAN_GENERIC_SOCKET_ERROR.
        */
        ssize_t xRead(uint8 *pu8buffer, size_t xBufferSize) const;

        /**
        * @brief Wait for event on file descriptor.
        * @param[in] i32Timeout Wait timeout
        * @return Number of sockets with the data pending.
        */
        int32 i32Poll(int32 i32Timeout) const;

    private:
        /**
        * @brief StreamCommunicator copy constructor.
        * @param[in, out] StreamCommunicator Reference to StreamCommunicator
        */
        StreamCommunicator(const StreamCommunicator&);

        /**
        * @brief StreamCommunicator assignment operator.
        * @param[in, out] StreamCommunicator Reference to StreamCommunicator
        */
        StreamCommunicator& operator=(const StreamCommunicator&);

        /**
        * Locally stored TCP socket descriptor.
        */
        int32 i32TCPSocketFD;
    };
}

#endif /* MMAN__STREAMCOMMUNICATOR_HPP_ */

