/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_ca.cpp
*
* Description  : Manifest manager, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent.
****************************************************************************/

#include <ace/rw_mutex.h>

#include "mman_systemfacade.hpp"
#include "mman_task.hpp"

namespace
{
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is initialized before a call to MMAN_v(De)Init> */
    ACE_RW_Mutex g_TaskLock;
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is created and destroyed during runtime> */
    manifest_manager::SystemFacade *poManifestManager = NULL;
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is created and destroyed during runtime> */
    manifest_manager::ManifestBroadcasterTask *poManifestBroadcaster = NULL;
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is created and destroyed during runtime> */
    manifest_manager::TCPRequestHandlerTask *poTCPRequestHandler = NULL;
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is created and destroyed during runtime> */
    manifest_manager::TCPRequestProcessorTask *poTCPRequestProcessor = NULL;
    /* <@QACPP: 2310> <RelLineCount: 1> <SWQE: 20201016, D. Wagner> <Comment: Object is created and destroyed during runtime> */
    manifest_manager::TCPRequestProcessorTask *poTCPRequestProcessorTwo = NULL;
}

extern "C"
{
	void MMAN_vInit(void)
	{
        ACE_Write_Guard<ACE_RW_Mutex> guard(g_TaskLock);
        if (poManifestManager == NULL)
        {
            poManifestManager = new manifest_manager::SystemFacade();
        }
        if (poManifestBroadcaster == NULL)
        {
            manifest_manager::ManifestBroadcasterTask *poTask(
                new manifest_manager::ManifestBroadcasterTask(*poManifestManager));
            if (poTask->open(0))
                poManifestBroadcaster = poTask;
        }
        if (poTCPRequestHandler == NULL)
        {
            manifest_manager::TCPRequestHandlerTask *poTask(
                new manifest_manager::TCPRequestHandlerTask(*poManifestManager));
            if (poTask->open(0))
                poTCPRequestHandler = poTask;
        }
        if (poTCPRequestProcessor == NULL)
        {
            manifest_manager::TCPRequestProcessorTask *poTask(
                new manifest_manager::TCPRequestProcessorTask(*poManifestManager));
            if (poTask->open(0))
                poTCPRequestProcessor = poTask;
        }
        if (poTCPRequestProcessorTwo == NULL)
        {
            manifest_manager::TCPRequestProcessorTask *poTask(
                new manifest_manager::TCPRequestProcessorTask(*poManifestManager));
            if (poTask->open(0))
                poTCPRequestProcessorTwo = poTask;
        }
	}

	void MMAN_vDeinit(void)
	{
        ACE_Write_Guard<ACE_RW_Mutex> guard(g_TaskLock);
        if (poManifestBroadcaster != NULL)
        {
            poManifestBroadcaster->stopTask();
            delete poManifestBroadcaster;
            poManifestBroadcaster = NULL;
        }
        if (poTCPRequestHandler != NULL)
        {
            poTCPRequestHandler->stopTask();
            delete poTCPRequestHandler;
            poTCPRequestHandler = NULL;
        }
        if (poTCPRequestProcessor != NULL)
        {
            poTCPRequestProcessor->stopTask();
            delete poTCPRequestProcessor;
            poTCPRequestProcessor = NULL;
        }
        if (poTCPRequestProcessorTwo != NULL)
        {
            poTCPRequestProcessorTwo->stopTask();
            delete poTCPRequestProcessorTwo;
            poTCPRequestProcessorTwo = NULL;
        }
        if (poManifestManager != NULL)
        {
            delete poManifestManager;
            poManifestManager = NULL;
        }
	}
}

bool MMAN_boIsServiceActionPermitted(
    const uint8 *pu8SourceIPAddress,
    const uint8 *pu8DestinationIPAddress,
    uint16 u16PortNumber,
    manifest_manager::tenCommunicationProtocol enProtocol,
    manifest_manager::tenSecurityLevel enSecurityLevel,
    uint16 u16ServiceID)
{
    bool boResult = false;

    if (poManifestManager != NULL)
    {
        boResult = poManifestManager->boIsServiceActionPermitted(
            pu8SourceIPAddress,
            pu8DestinationIPAddress,
            u16PortNumber,
            enProtocol,
            enSecurityLevel,
            u16ServiceID);
    }

    return boResult;
}