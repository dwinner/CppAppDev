/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capabilitydbif.cpp
*
* Description  : Manifest manager, capability database interface implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#include <string.h>

#include "mman__capabilitydbif.hpp"

namespace manifest_manager
{
    bool CapabilityDatabaseIf::boHasSpecifiedEntry(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry)
    {
        bool boResult;

        boResult = boFindEntry(stCapabilityDatabaseEntry);

        return boResult;
    }

    bool CapabilityDatabaseIf::boFindEntry(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry)
    {
        bool boEntryFound = false;

        for (uint16 u16Index = 0; u16Index < MMAN__nCapabilityDatabaseSize; u16Index++)
        {
            boEntryFound =
                (memcmp(
                &MMAN__astCapabilityDatabase[u16Index].au8SourceIPAddress[0], 
                &stCapabilityDatabaseEntry.au8SourceIPAddress[0], 
                MMAN_nEndpointAddressLenght) == 0) &&
                (memcmp(
                &MMAN__astCapabilityDatabase[u16Index].au8DestinationIPAddress[0], 
                &stCapabilityDatabaseEntry.au8DestinationIPAddress[0], 
                MMAN_nEndpointAddressLenght) == 0) &&
                (MMAN__astCapabilityDatabase[u16Index].u16PortNumber == stCapabilityDatabaseEntry.u16PortNumber) &&
                (MMAN__astCapabilityDatabase[u16Index].enProtocol == stCapabilityDatabaseEntry.enProtocol) &&
                (MMAN__astCapabilityDatabase[u16Index].enSecurityLevel == stCapabilityDatabaseEntry.enSecurityLevel) &&
                (MMAN__astCapabilityDatabase[u16Index].u16ServiceID == stCapabilityDatabaseEntry.u16ServiceID);

            if (boEntryFound)
            {
                break;
            }
        }

        return boEntryFound;
    }
}