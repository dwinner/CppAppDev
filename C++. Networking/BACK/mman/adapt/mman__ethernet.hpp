/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__ethernet.hpp
*
* Description  : Manifest manager, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__ETHERNET_HPP_
#define MMAN__ETHERNET_HPP_

#include "mman_shared.h"

/* System Headerfiles */
extern "C" {
#include "cdef.h"
}

namespace manifest_manager
{
    extern const uint8 MMAN__au8LocalEndpointAddress[MMAN_nEndpointAddressLenght];

    extern const uint8 MMAN__au8RemoteEndpointMulticastAddress[MMAN_nEndpointAddressLenght];
}

#endif /* MMAN__ETHERNET_HPP_ */