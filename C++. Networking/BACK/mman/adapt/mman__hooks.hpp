/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__hooks.hpp
*
* Description  : Manifest manager, hooks, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__HOOKS_HPP_
#define MMAN__HOOKS_HPP_

#include "mman__provisioningserver.hpp"

extern "C"
{
#include <cdef.h>
}

namespace manifest_manager
{
    /**
    * @brief Container for system specific hooks
    */
    class Hooks
    {
    public:
        /**
        * @brief Hook to report an error in a system specific way.
        * @param[in] pcFile File in which the error occurred
        * @param[in] u32Line Line number in which the error occurred
        * @param[in] u16ErrorId ID of error
        * @param[in] i32Details Additional details of error
        */
        static void vReportError(const char *pcFile, uint32 u32Line, uint16 u16ErrorId, int32 i32Details);

        /**
        * @brief Hook to get network state
        * @return State of network
        */
        static ProvisioningServer::tenNetworkStates enGetNetworkState(void);
    };
}

#endif /* MMAN__HOOKS_HPP_ */
