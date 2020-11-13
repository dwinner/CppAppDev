/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_shared.cpp
*
* Description  : Manifest manager, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN_SHARED_H_
#define MMAN_SHARED_H_

/**
* Description: UDP port number to broadcast manifest digest over
*/
#define MMAN_UDP_PORT_NUMBER 42515U

/**
* Description: TCP port number to accept all new connections to
*/
#define MMAN_TCP_PORT_NUMBER 29801U

/**
* Description: Endpoint address length in bytes
*/
#define MMAN_nEndpointAddressLenght 16U

#ifdef __cplusplus
namespace manifest_manager
{
    /**
    * Available protocols used by capability cache
    */
    enum tenCommunicationProtocol
    {
        nenUDP = 0,
        nenTCP = 1,
    };

    /**
    * Available protocols used by capability cache
    */
    enum tenSecurityLevel
    {
        nenNone         = 0,
        nenAuthentic    = 1,
    };
}
#endif

#endif /* MMAN_SHARED_H_ */