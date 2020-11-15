/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__hooks.cpp
*
* Description  : Manifest manager, implementation of hooks
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#include <stdio.h> // for printf

#include "mman__hooks.hpp"
#include "mman__errorhandler.hpp"

#ifdef __cplusplus
extern "C" {
#endif
#include "EXEA_c1.h"
#include "CRHDL_c1.h"
#ifdef __cplusplus
}
#endif

namespace manifest_manager
{
    void Hooks::vReportError(const char *pcFile, uint32 u32Line, uint16 u16ErrorId, int32 i32Details)
    {
        switch (u16ErrorId)
        {
        case ErrorHandler::nenNullPointer: u16ErrorId = MMAN_nenErrNullPointer; break;
        case ErrorHandler::nenInvalidSocketFileDescriptor: u16ErrorId = MMAN_nenInvalidSocketFileDescriptor; break;
        case ErrorHandler::nenSocketBindFailure: u16ErrorId = MMAN_nenSocketBindFailure; break;
        case ErrorHandler::nenSocketListenFailure: u16ErrorId = MMAN_nenSocketListenFailure; break;
        case ErrorHandler::nenSocketShutdownFailure: u16ErrorId = MMAN_nenSocketShutdownFailure; break;
        case ErrorHandler::nenSocketOptionIPv6UnicastHopLimitFailure: u16ErrorId = MMAN_nenSocketOptionIPv6UnicastHopLimitFailure; break;
        case ErrorHandler::nenSocketOptionReuseAddrFailure: u16ErrorId = MMAN_nenSocketOptionReuseAddrFailure; break;
        case ErrorHandler::nenSocketOptionIPv6MulticastIFFailure: u16ErrorId = MMAN_nenSocketOptionIPv6MulticastIFFailure; break;
        case ErrorHandler::nenSocketOptionIPv6MulticastLoopFailure: u16ErrorId = MMAN_nenSocketOptionIPv6MulticastLoopFailure; break;
        case ErrorHandler::nenSocketOptionIPv6MulticastHopsFailure: u16ErrorId = MMAN_nenSocketOptionIPv6MulticastHopsFailure; break;
        default: u16ErrorId = MMAN_nenErrUnknown; break;
        }

        EXEA_vHandleException(EXEA_MMAN, (EXEA_tenErrorID)(u16ErrorId), (u32Line), (i32Details));

        printf("[Manifest manager] %s:%u Error %d (%d)\n", pcFile, u32Line, u16ErrorId, i32Details);
    }

    ProvisioningServer::tenNetworkStates Hooks::enGetNetworkState(void)
    {
        return (CRHDL_enStateHdlGetState(CRHDL_nSMSRES_Ethernet_FullComm) == CRHDL_nStateOn) ? ProvisioningServer::nenNetworkIsUp : ProvisioningServer::nenNetworkIsDown;
    }
}