/**
 * h264Splitter.c
 *
 */

#include <stdio.h>
#include <string.h>

#ifdef STARTER264NAL4
int STARTER264NAL = 4;
unsigned char starter[] = {0, 0, 0, 1};
#else
int STARTER264NAL = 3;
unsigned char starter[] = {0, 0, 1};
#endif

#define MAX_BUFFER_SIZE 256

int main(int argc, const char *argv[])
{
    const char *h264FileName = argv[1];
    FILE *h264File = fopen(h264FileName, "rb");
    char fileName[50];
    unsigned char data[MAX_BUFFER_SIZE];
    unsigned char tmp[MAX_BUFFER_SIZE];
    unsigned char *head;
    unsigned char *tail;
    unsigned char *DATA_TAIL;
    memset(data, 0, MAX_BUFFER_SIZE);

    long int nalIdx = 0;
    FILE *nalUnit = NULL;

    DATA_TAIL = data + MAX_BUFFER_SIZE - 1;
    head = data;

    while (1)
    {
        int len = fread(head, DATA_TAIL - head + 1, 1, h264File);
        if (len <= 0)
        {
            fclose(nalUnit);
            break;
        }

        tail = data;
        head -= STARTER264NAL - 1;

        while (head < DATA_TAIL - (STARTER264NAL - 2))
        {
            if (memcmp(head, starter, STARTER264NAL) == 0)
            {
                if (nalUnit != NULL)
                {
                    fwrite(tail, head - tail, 1, nalUnit);
                    fclose(nalUnit);
                }

                tail = head;
                printf("New NAL unit created %ld\n", nalIdx);
                sprintf(fileName, "%s.%04ld", h264FileName, nalIdx);
                nalUnit = fopen(fileName, "wb");
                nalIdx++;
            }

            head++;
        }

        if (data == tail)
        {
            fwrite(tail, head - tail, 1, nalUnit);
            memcpy(tmp, head, DATA_TAIL - head + 1);
            memcpy(data, tmp, DATA_TAIL - head + 1);
            head = data + (DATA_TAIL - head + 1);
        }
        else
        {
            memcpy(tmp, tail, DATA_TAIL - tail + 1);
            memcpy(data, tmp, DATA_TAIL - tail + 1);
            head = data + (DATA_TAIL - tail + 1);
        }
    }

    fwrite(data, (DATA_TAIL - data), 1, nalUnit);
    fclose(nalUnit);
    fclose(h264File);

    return 0;
}
