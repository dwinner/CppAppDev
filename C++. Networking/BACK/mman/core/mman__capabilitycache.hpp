/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capbilitycache.hpp
*
* Description  : Manifest manager, capability cache, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent
****************************************************************************/

#ifndef MMAN__CAPABILITYCACHE_HPP_
#define MMAN__CAPABILITYCACHE_HPP_

#include "mman__capabilitydbif.hpp"

namespace manifest_manager
{
    class CapabilityCache
    {
    public:
        /**
        * @brief Capability cache constructor.
        */
        CapabilityCache(void):
            oCapabilityDatabase()
        {}

        /**
        * @brief Creates a new job inside the internal list and returns a pointer to it.
        * @param[in] stCapabilityDatabaseEntry Capability database item
        * @return Permission status.
        */
        bool boIsActionPermitted(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry);

    private:
        /**
        * Capability database interface object.
        */
        CapabilityDatabaseIf oCapabilityDatabase;
    };
}

#endif /* MMAN__CAPABILITYCACHE_HPP_ */