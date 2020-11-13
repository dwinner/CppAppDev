/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__ethernet.cpp
*
* Description  : Manifest manager, package - internal data
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent.
****************************************************************************/

#include "mman__ethernet.hpp"

namespace manifest_manager
{
    /**
    * Description: Local IPv6 address of a device
    */
    const uint8 MMAN__au8LocalEndpointAddress[MMAN_nEndpointAddressLenght] = {
        0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14
    };

    /**
    * Description: Multicas IPv6 address of a remote device
    */
    const uint8 MMAN__au8RemoteEndpointMulticastAddress[MMAN_nEndpointAddressLenght] = {
        0xff, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00
    };
}

