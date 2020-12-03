#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

namespace mman
{
   /**
    * Length (in bytes) of a locally stored manifest's digest. Is generated outside.
    * Must be updated in case of an external request to change manifest collection inside IC
    */
   constexpr int LocalManifestDigestLenght = 26;

   /**
    * Length (in bytes) of a locally stored UDP - broadcasted message. containing digest/SHA256 hash
    * Is generated outside. Must be updated in case of an external request to change manifest collection inside IC
    */
   constexpr int ManifestMulticastMsgLength = 28;

   /**
    * Length (in bytes) of a locally stored TCP response message with manifest included.
    * Is generated outside.
    * Must be updated in case of an external request to change manifest collection inside IC
    */
   constexpr int ManifestResponsetMsgLength = 1777;

   /**
    * Length (in bytes) of a locally stored TCP response message without manifest included.
    * Is generated outside.
    * Must be updated in case of an external request to change manifest collection inside IC
    */
   constexpr int EmptyResponsetMsgLength = 26;

   extern const char LocalManifestDigest[LocalManifestDigestLenght];
   extern const char ManifestMulticastMsg[ManifestMulticastMsgLength];
   extern const char ManifestResponseMsg[ManifestResponsetMsgLength];
   extern const char ManifestEmptyResponseMsg[EmptyResponsetMsgLength];
}
