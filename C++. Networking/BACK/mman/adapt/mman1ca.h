/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : MMAN_ca.h
*
* Description  : Manifest manager, external interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN_CA_H_
#define MMAN_CA_H_

#include "mman_shared.h"

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
bool MMAN_boIsServiceActionPermitted(
    const uint8 *pu8SourceIPAddress,
    const uint8 *pu8DestinationIPAddress,
    uint16 u16PortNumber,
    manifest_manager::tenCommunicationProtocol enProtocol,
    manifest_manager::tenSecurityLevel enSecurityLevel,
    uint16 u16ServiceID);

#endif /* MMAN_CA_H_ */

