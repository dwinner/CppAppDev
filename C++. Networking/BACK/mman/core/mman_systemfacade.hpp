/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_systemfacade.hpp
*
* Description  : Manifest manager, system facade, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN_SYSTEMFACADE_HPP_
#define MMAN_SYSTEMFACADE_HPP_

#include "mman__provisioningserver.hpp"
#include "mman__capabilitycache.hpp"

namespace manifest_manager
{
    class SystemFacade
    {
    public:
        /**
        * @brief System facade constructor.
        */
        SystemFacade(void) :
            oProvisioningServer(),
            oCapabilityCache()
        {}

        /**
        * @brief Start provisioning server wrapper.
        */
        void vBroadcastManifest(void);

        /**
        * @brief Stop provisioning server wrapper.
        */
        void vHandleTCPRequest(void);

        /**
        * @brief Stop provisioning server wrapper.
        */
        void vProcessTCPRequest(void);

        /**
        * @brief Check service permissions.
        * @param[in] pu8SourceIPAddress Source endpoint address
        * @param[in] pu8DestinationIPAddress Destination endpoint address
        * @param[in] u16PortNumber Destination endpoint port number
        * @param[in] enProtocol Used protocol
        * @param[in] enSecurityLevel Security level
        * @param[in] u16ServiceID Service ID
        * @return Permission status.
        */
        bool boIsServiceActionPermitted(
            const uint8 *pu8SourceIPAddress,
            const uint8 *pu8DestinationIPAddress,
            uint16 u16PortNumber,
            manifest_manager::tenCommunicationProtocol enProtocol,
            manifest_manager::tenSecurityLevel enSecurityLevel,
            uint16 u16ServiceID);

    private:
        /**
        * @brief SystemFacade copy constructor.
        * @param[in, out] SystemFacade Reference to SystemFacade
        */
        SystemFacade(const SystemFacade&);

        /**
        * @brief SystemFacade assignment operator.
        * @param[in, out] SystemFacade Reference to SystemFacade
        */
        SystemFacade& operator=(const SystemFacade&);

        /**
        * Provisioning server object.
        */
        ProvisioningServer oProvisioningServer;

        /**
        * Capability cache object.
        */
        CapabilityCache oCapabilityCache;
    };
}

#endif /* MMAN_SYSTEMFACADE_HPP_ */

