#pragma once

/*
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdlib.h"

#ifdef __cplusplus
}
#endif
*/

/**
 * Length (in bytes) of a locally stored manifest's digest. Is generated outside.
 * Must be updated in case of an external request to change manifest collection inside IC
 */
#define LOCAL_MANIFEST_DIGEST_LENGHT (26)

/**
 * Length (in bytes) of a locally stored UDP - broadcasted message. containing digest/SHA256 hash
 * Is generated outside. Must be updated in case of an external request to change manifest collection inside IC
 */
#define MANIFEST_BROADCAST_MSG_LENGTH (28)

/**
 * Length (in bytes) of a locally stored TCP response message with manifest included.
 * Is generated outside.
 * Must be updated in case of an external request to change manifest collection inside IC
 */
#define MANIFEST_RESPONSET_MSG_LENGTH (1777)

/**
 * Length (in bytes) of a locally stored TCP response message without manifest included.
 * Is generated outside.
 * Must be updated in case of an external request to change manifest collection inside IC
 */
#define EMPTY_RESPONSET_MSG_LENGTH (26)

namespace mman
{
	extern const unsigned char LocalManifestDigest[LOCAL_MANIFEST_DIGEST_LENGHT];
	extern const /*unsigned*/ char ManifestBroadcastMsg[MANIFEST_BROADCAST_MSG_LENGTH];
	extern const unsigned char ManifestResponseMsg[MANIFEST_RESPONSET_MSG_LENGTH];
	extern const unsigned char ManifestEmptyResponseMsg[EMPTY_RESPONSET_MSG_LENGTH];
}
