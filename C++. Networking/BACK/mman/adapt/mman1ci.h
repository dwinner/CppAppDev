/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_ci.h
*
* Description  : Manifest manager, package - internal data
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent.
****************************************************************************/

#ifndef MMAN_CI_H_
#define MMAN_CI_H_

#include "mman_shared.h"

/* System Headerfiles */
#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

/**
* Description: Delay in microseconds between manifest digest broadcast events
*/
#define MMAN__nBroadcastDelay 200000U

/**
* Description: Size of a buffer used to accept TCP requests
*/
#define MMAN__nTCPRequestBufferSize MMAN__nLocalManifestDigestLenght

/**
* Description: Delay between poll events for TCP connections
*/
#define MMAN__nTCPConnectionTimeout 500U

/**
* Description: Length of queue containing pending connections
*/
#define MMAN__nTCPSocketBacklogSize 10U

/**
* Description: Number of TCP sockets used in manifest manager.
* Used for "poll" function
*/
#define MMAN__nNumberOfTCPSockets 1U

/**
* Description: Maximal number of concurrently processed TCP connections.
*/
#define MMAN__nMaxNumberOfConcurrentConnections 5U

/**
* Description: Timeout for 'select' socket operation, microseconds.
*/
#define MMAN__nSocketSelectTimeout 100000U

#endif /* MMAN_CI_H_ */

