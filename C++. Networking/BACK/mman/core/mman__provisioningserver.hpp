/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__provisioningserver.hpp
*
* Description  : Manifest manager, internal interface, provisioning server
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS dependent.
****************************************************************************/

#ifndef MMAN__PROVISIONINGSERVER_HPP_
#define MMAN__PROVISIONINGSERVER_HPP_

#include <ace/guard_t.h>
#include <ace/rw_mutex.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

#include "mman_shared.h"
#include "mman__streamcommunicator.hpp"
#include "mman__udpmulticastsendersocket.hpp"
#include "mman__tcpserverconnector.hpp"

#define MMAN__nMaxNumberOfElementsInQueue 5

namespace manifest_manager
{
    template <class T>
    class Queue
    {
    public:
        /**
        * @brief Queue constructor.
        */
        Queue(void) :
            oQueueLock(),
            u8HeadPosition(0),
            u8TailPosition(0),
            u8CountOfElements(0)
        {
            vEmptyQueue(false);
        }

        /**
        * @brief Queue destructor.
        */
        ~Queue(void)
        {
            vEmptyQueue(true);
        }

        /**
        * @brief Queue - push operation.
        * @param[in, out] poElement Element to be pushed
        * @return Status of the operation
        */
        bool boPush(T *poElement)
        {
            bool boResult = false;

            ACE_Write_Guard<ACE_RW_Mutex> oGuard(oQueueLock);

            if (u8CountOfElements < MMAN__nMaxNumberOfElementsInQueue)
            {
                apoElements[u8HeadPosition++] = poElement;
                boResult = true;
                u8CountOfElements++;
            }
            if (u8HeadPosition == MMAN__nMaxNumberOfElementsInQueue)
            {
                u8HeadPosition = 0;
            }

            return boResult;
        }

        /**
        * @brief Queue - pop operation.
        * @return Extracted element
        */
        T *poPop(void)
        {
            T *poReturnValue = NULL;

            ACE_Write_Guard<ACE_RW_Mutex> oGuard(oQueueLock);

            if (u8CountOfElements >= 1)
            {
                poReturnValue = apoElements[u8TailPosition++];
                apoElements[u8TailPosition - 1] = NULL;
                u8CountOfElements--;
            }
            if (u8TailPosition == MMAN__nMaxNumberOfElementsInQueue)
            {
                u8TailPosition = 0;
            }

            return poReturnValue;
        }

    private:
        /**
        * @brief Destroy all elements in a queue
        * @param[in] boShouldDelete Flag indicating whether the memory should be freed or not
        */
        void vEmptyQueue(bool boShouldDelete)
        {
            for (uint8 u8Index = 0; u8Index < MMAN__nMaxNumberOfElementsInQueue; u8Index++)
            {
                if (boShouldDelete)
                {
                    delete apoElements[u8Index];
                }
                apoElements[u8Index] = NULL;
            }
        }

        /**
        * @brief Queue copy constructor.
        * @param[in, out] Queue Reference to Queue
        */
        Queue(const Queue&);

        /**
        * @brief Queue assignment operator.
        * @param[in, out] Queue Reference to Queue
        */
        Queue& operator=(const Queue&);

        /**
        * Queue container.
        */
        T *apoElements[MMAN__nMaxNumberOfElementsInQueue];

        /**
        * Syncronization mutex.
        */
        ACE_RW_Mutex oQueueLock;

        /**
        * Queue's head.
        */
        uint8 u8HeadPosition;

        /**
        * Queue's tail.
        */
        uint8 u8TailPosition;

        /**
        * Count of elements in queue.
        */
        uint8 u8CountOfElements;
    };

    class ProvisioningServer
    {
    public:
        /**
        * @brief Provisioning server constructor.
        */
        ProvisioningServer(void):
            oUdpBroadcaster(MMAN_UDP_PORT_NUMBER),
            oRemoteRequestConnector(MMAN_TCP_PORT_NUMBER)
        {}

        /**
        * @brief Broadcast thread worker.
        */
        void vBroadcastManifestDigest(void);

        /**
        * @brief TCP request handling worker. Tries to establish new TCP connections
        */
        void vRemoteRequestHandler(void);

        /**
        * @brief TCP request processing worker. Processes TCP requests.
        */
        void vRemoteRequestProcessor(void);

        /**
        * States of network subsystem.
        */
        enum tenNetworkStates
        {
            nenNetworkIsDown,
            nenNetworkIsUp,
        };

    private:
        /**
        * @brief ProvisioningServer copy constructor.
        * @param[in, out] ProvisioningServer Reference to ProvisioningServer
        */
        ProvisioningServer(const ProvisioningServer&);

        /**
        * @brief ProvisioningServer assignment operator.
        * @param[in, out] ProvisioningServer Reference to ProvisioningServer
        */
        ProvisioningServer& operator=(const ProvisioningServer&);

        /**
        * @brief Outputs local collection on TCP request.
        * @param[in] oCommunicator Stream communicator object
        */
        void vProvideLocalCollection(StreamCommunicator &oCommunicator);

        /**
        * @brief Outputs empty local collection on TCP request.
        * @param[in] oCommunicator Stream communicator object
        */
        void vProvideEmptyCollection(StreamCommunicator &oCommunicator);

        /**
        * @brief Check network state
        * @return Network state
        */
        tenNetworkStates enGetNetworkState(void) const;

        /**
        * UDP broadcaster object.
        */
        UdpMulticastSenderSocket oUdpBroadcaster;

        /**
        * TcpServerConnector object.
        */
        TcpServerConnector oRemoteRequestConnector;

        /**
        * Queue<StreamCommunicator> object.
        */
        Queue<StreamCommunicator> oQueue;
    };
}

#endif /* MMAN__PROVISIONINGSERVER_HPP_ */

