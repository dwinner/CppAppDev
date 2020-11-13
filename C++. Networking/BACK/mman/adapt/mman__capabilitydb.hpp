/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capabilitydb.hpp
*
* Description  : Manifest manager, capability database, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__CAPABILITYDB_HPP_
#define MMAN__CAPABILITYDB_HPP_

#include "mman_shared.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

/**
* Capability database size
*/
#define MMAN__nCapabilityDatabaseSize (uint16)42

namespace manifest_manager
{
    /**
    * Capability database item structure
    */
    struct tCapabilityDatabaseEntry
    {
        uint8 au8SourceIPAddress[MMAN_nEndpointAddressLenght];
        uint8 au8DestinationIPAddress[MMAN_nEndpointAddressLenght];
        uint16 u16PortNumber;
        tenCommunicationProtocol enProtocol;
        tenSecurityLevel enSecurityLevel;
        uint16 u16ServiceID;
    };

    extern tCapabilityDatabaseEntry MMAN__astCapabilityDatabase[MMAN__nCapabilityDatabaseSize];
}

#endif /* MMAN__CAPABILITYDB_HPP_ */