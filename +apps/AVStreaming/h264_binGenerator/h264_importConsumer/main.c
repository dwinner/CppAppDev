#include <stdio.h>
#include "test_noloop.h264_bin.h"

int main()
{
    for (size_t i = 0; i < PAYLOAD_UNIT_SIZE; i++)
    {
        VIDEORTP_payloadUnit_t payloadItem = payloadUnits[i];
        uint8_t *content = (uint8_t *) payloadItem.buffer;
        size_t length = payloadItem.length;

        printf("Length: %d\n", length);
        printf("Data:\n");
        for (size_t j = 0; j < length; j++)
        {
            uint8_t dataItem = content[j];
            printf(" %02x", dataItem);
            if ((j + 1) % 16 == 0)
            {
                printf("\n");
            }
        }
    }

    return 0;
}
