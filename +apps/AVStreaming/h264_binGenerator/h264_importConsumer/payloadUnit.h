#ifndef H264_IMPORTCONSUMER_PAYLOADUNIT_H
#define H264_IMPORTCONSUMER_PAYLOADUNIT_H

/**
 * @brief This struct contain payload buffer and length, used for one element in array
 *
 */

typedef struct VIDEORTP_payloadUnit_t
{
   const void *buffer;
   size_t length;
} VIDEORTP_payloadUnit_t;

#endif //H264_IMPORTCONSUMER_PAYLOADUNIT_H
