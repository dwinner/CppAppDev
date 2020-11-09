/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman_ce.h
*
* Description  : Manifest manager, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN_CE_H_
#define MMAN_CE_H_

#include <memory>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cdef.h"

#ifdef __cplusplus
}
#endif

/**
* Description: Socket generic error flag
*/
#define MMAN_GENERIC_SOCKET_ERROR -1

/**
* Description: Socket generic error flag
*/
#define MMAN_OK 0U

/**
* Description: Indication of failure on ACE side during thread creation / spawning
*/
#define MMAN_ACE_THREAD_CREATION_ERROR -1

#endif /* MMAN_CE_H_ */

