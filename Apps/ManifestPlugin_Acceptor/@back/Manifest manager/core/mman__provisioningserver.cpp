/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__provisioningserver.cpp
*
* Description  : Manifest manager, provisioning server implementation
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent.
****************************************************************************/

#include "mman_ci.h"
#include "mman__provisioningserver.hpp"
#include "mman__tcpserverconnector.hpp"
#include "mman__errorhandler.hpp"
#include "mman__manifeststorage.hpp"
#include "mman__hooks.hpp"

namespace manifest_manager
{
    void ProvisioningServer::vBroadcastManifestDigest(void)
    {
        if (enGetNetworkState() == ProvisioningServer::nenNetworkIsUp)
        {
            oUdpBroadcaster.xSend(&MMAN__au8ManifestBroadcastMsg[0], MMAN__nManifestBroadcastMsgLength);
        }
    }

    void ProvisioningServer::vRemoteRequestHandler(void)
    {
        StreamCommunicator *poCommunicator = NULL;

        if (enGetNetworkState() == ProvisioningServer::nenNetworkIsUp)
        {
            poCommunicator = oRemoteRequestConnector.poEstablishConnection();
        }

        if (poCommunicator != NULL)
        {
            if (!oQueue.boPush(poCommunicator))
            {
                // Manually free up the memory
                delete poCommunicator;
                poCommunicator = NULL;
            }
        }
    }

    void ProvisioningServer::vRemoteRequestProcessor(void)
    {
        StreamCommunicator *poCommunicator = oQueue.poPop();

        if (poCommunicator != NULL)
        {
            if (enGetNetworkState() == ProvisioningServer::nenNetworkIsUp)
            {
                if (poCommunicator->i32Poll(MMAN__nTCPConnectionTimeout) == MMAN__nNumberOfTCPSockets)
                {
                    uint8 au8RequestBuffer[MMAN__nTCPRequestBufferSize];

                    ssize_t xReadBytes = poCommunicator->xRead(&au8RequestBuffer[0], MMAN__nTCPRequestBufferSize);

                    if (xReadBytes == MMAN__nLocalManifestDigestLenght)
                    {
                        if (memcmp(
                            &au8RequestBuffer[0],
                            &MMAN__au8LocalManifestDigest[0],
                            MMAN__nLocalManifestDigestLenght) == 0)
                        {
                            ProvisioningServer::vProvideLocalCollection(*poCommunicator);

                        }
                        else
                        {
                            ProvisioningServer::vProvideEmptyCollection(*poCommunicator);
                        }
                    }
                }
            }

            // Manually free up the memory
            delete poCommunicator;
            poCommunicator = NULL;
        }
    }

    void ProvisioningServer::vProvideLocalCollection(StreamCommunicator &oCommunicator)
    {
        oCommunicator.xWrite(
            &MMAN__au8ManifestResponseMsg[0],
            MMAN__nManifestResponsetMsgLength);
    }

    void ProvisioningServer::vProvideEmptyCollection(StreamCommunicator &oCommunicator)
    {
        oCommunicator.xWrite(
            &MMAN__au8ManifestEmptyResponseMsg[0],
            MMAN__nManifestEmptyResponsetMsgLength);
    }

    ProvisioningServer::tenNetworkStates ProvisioningServer::enGetNetworkState(void) const
    {
        return Hooks::enGetNetworkState();
    }
}