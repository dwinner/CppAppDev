/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capbilitycache.cpp
*
* Description  : Manifest manager, capability cache implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#include "mman__capabilitycache.hpp"

namespace manifest_manager
{
    bool CapabilityCache::boIsActionPermitted(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry)
    {
        bool boResult;

        boResult = oCapabilityDatabase.boHasSpecifiedEntry(stCapabilityDatabaseEntry);

        return boResult;
    }
}