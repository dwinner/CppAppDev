/***************************************************************************
*======= Copyright by Continental AG ========
****************************************************************************
* Title        : mman__manifeststorage.hpp
*
* Description  : Manifest manager, manifest storage, internal interface
*
* Responsible  : Kirill Bogomolov
*
* Environment  : Processor and OS independent
****************************************************************************/

#ifndef MMAN__MANIFESTSTORAGE_HPP_
#define MMAN__MANIFESTSTORAGE_HPP_

/* System Headerfiles */
extern "C" {
#include "cdef.h"
}

/**
* Description: Length (in bytes) of a locally stored manifest's digest.
* Is generated
*/
#define MMAN__nLocalManifestDigestLenght (uint8)26

/**
* Description: Length (in bytes) of a locally stored UDP - broadcasted message.
* containing digest/SHA256 hash
* Is generated
*/
#define MMAN__nManifestBroadcastMsgLength (uint8)28

/**
* Description: Length (in bytes) of a locally stored TCP response message with manifest included.
* Is generated
*/
#define MMAN__nManifestResponsetMsgLength (uint16)1777

/**
* Description: Length (in bytes) of a locally stored TCP response message without manifest included.
* Is generated
*/
#define MMAN__nManifestEmptyResponsetMsgLength (uint8)26

namespace manifest_manager
{
    extern const uint8 MMAN__au8LocalManifestDigest[MMAN__nLocalManifestDigestLenght];

    extern const uint8 MMAN__au8ManifestBroadcastMsg[MMAN__nManifestBroadcastMsgLength];

    extern const uint8 MMAN__au8ManifestResponseMsg[MMAN__nManifestResponsetMsgLength];

    extern const uint8 MMAN__au8ManifestEmptyResponseMsg[MMAN__nManifestEmptyResponsetMsgLength];
}

#endif /* MMAN__MANIFESTSTORAGE_HPP_ */