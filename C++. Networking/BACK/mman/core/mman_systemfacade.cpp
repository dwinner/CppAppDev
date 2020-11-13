/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_systemfacade.hpp
*
* Description  : Manifest manager, system facade
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#include "mman_systemfacade.hpp"

namespace manifest_manager
{
    void SystemFacade::vBroadcastManifest(void)
    {
        oProvisioningServer.vBroadcastManifestDigest();
    }

    void SystemFacade::vHandleTCPRequest(void)
    {
        oProvisioningServer.vRemoteRequestHandler();
    }

    void SystemFacade::vProcessTCPRequest(void)
    {
        oProvisioningServer.vRemoteRequestProcessor();
    }

    bool SystemFacade::boIsServiceActionPermitted(
        const uint8 *pu8SourceIPAddress,
        const uint8 *pu8DestinationIPAddress,
        uint16 u16PortNumber,
        manifest_manager::tenCommunicationProtocol enProtocol,
        manifest_manager::tenSecurityLevel enSecurityLevel,
        uint16 u16ServiceID)
    {
        bool boResult;

        tCapabilityDatabaseEntry stCapabilityDatabaseEntry =
        {
            {},
            {},
            u16PortNumber,
            enProtocol,
            enSecurityLevel,
            u16ServiceID,
        };

        memcpy(&stCapabilityDatabaseEntry.au8SourceIPAddress[0], pu8SourceIPAddress, MMAN_nEndpointAddressLenght);
        memcpy(&stCapabilityDatabaseEntry.au8DestinationIPAddress[0], pu8DestinationIPAddress, MMAN_nEndpointAddressLenght);

        boResult = oCapabilityCache.boIsActionPermitted(stCapabilityDatabaseEntry);

        return boResult;
    }
}