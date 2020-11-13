/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__capabilitydbif.hpp
*
* Description  : Manifest manager, capability database interface, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__CAPABILITYDBIF_HPP_
#define MMAN__CAPABILITYDBIF_HPP_

#include "mman__capabilitydb.hpp"

namespace manifest_manager
{
    class CapabilityDatabaseIf
    {
    public:
        /**
        * @brief Capability database constructor.
        */
        CapabilityDatabaseIf(void)
        {}

        /**
        * @brief Wrapper for database search method.
        * @param[in] stCapabilityDatabaseEntry Capability database item
        * @return Search result.
        */
        bool boHasSpecifiedEntry(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry);

    private:
        /**
        * @brief Database search method.
        * @param[in] stCapabilityDatabaseEntry Capability database item
        * @return Search result.
        */
        bool boFindEntry(tCapabilityDatabaseEntry &stCapabilityDatabaseEntry);
    };
}

#endif /* MMAN__CAPABILITYDBIF_HPP_ */