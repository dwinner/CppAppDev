/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__errorhandler.hpp
*
* Description  : Manifest manager, error handler, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__ERRORHANDLER_HPP_
#define MMAN__ERRORHANDLER_HPP_

/****************************************************************************
** Header Files
****************************************************************************/

/* System Headerfiles */
extern "C" {
#include "cdef.h"
}

/**
* @brief Reports an error
* @note This macro automatically adds the file name and line number to the call of ErrorHandler::vReportError.
* @param[in] enErrorId ID of error (see ErrorHandler::tenErrorId)
* @param[in] i32Details Details to further describe situation
*/
#define MMAN__mReportError(enErrorId, i32Details) ErrorHandler::vReportError(enErrorId, i32Details, __FILE__, __LINE__)

namespace manifest_manager
{
    /**
    * @brief Error handler
    *
    * Currently just takes note of an error and doesn't process any further.
    */
    class ErrorHandler
    {
        /***************************************************************************
        *   Class Operations and Attributes
        ***************************************************************************/
    public:
        /**
        * @brief Error IDs that can be reported
        */
        enum tenErrorId
        {
            nenNullPointer = 0x01,                       ///< Internal interface called with null pointer.

            nenInvalidSocketFileDescriptor,              ///< Invalid socket file descriptor detected.
            nenSocketBindFailure,                        ///< Failed to bind sockaddr to a socket.
            nenSocketListenFailure,                      ///< Failed to call 'listen' on socket, e.g. failed to mark socket as passive.
            nenSocketShutdownFailure,                    ///< Failed to shutdown a socket.

            nenSocketOptionReuseAddrFailure,             ///< Failed to set socket option SO_REUSEADDR.
            nenSocketOptionIPv6UnicastHopLimitFailure,   ///< Failed to set socket option IPV6_UNICAST_HOPS.
            nenSocketOptionIPv6MulticastIFFailure,       ///< Failed to set socket option IPV6_MULTICAST_IF.
            nenSocketOptionIPv6MulticastLoopFailure,     ///< Failed to set socket option IPV6_MULTICAST_LOOP.
            nenSocketOptionIPv6MulticastHopsFailure,     ///< Failed to set socket option IPV6_MULTICAST_HOPS.
            
            nenErrUnknown,                               ///< Unknown error.
        };

        /**
        * @brief Reports an error
        * @note Most users will probably want to use the MMAN__mReportError(enErrorId, u32Details) macro instead of calling this method directly.
        * @param[in] enErrorId ID of error
        * @param[in] i32Details Details to further describe situation
        * @param[in] pcPath Path of file in which the error occurred
        * @param[in] u32Line Line number in which the error occurred
        */
        static void vReportError(tenErrorId enErrorId, int32 i32Details = 0, const char *pcPath = NULL, uint32 u32Line = 0);

    private:
        /**
        * @brief Gets the file name part from a path.
        * @note Returns a pointer to the same buffer as pcPath points to.
        * @param[in] pcPath Path to get file name from
        * @result Pointer to file name part, or NULL if an error occurred
        */
        static const char *pcGetFileName(const char *pcPath);
    };
}

#endif /* MMAN__ERRORHANDLER_HPP_ */
