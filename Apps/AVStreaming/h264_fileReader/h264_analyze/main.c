/**
 * H.264 stream analyzer
 * (GCC) Simple usage: h264_analyze <someFile.H264> -o nalu.log
 */

#include "../h264_streamLib/h264_stream.h"
#include "../h264_streamLib/h264_nal.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define H264_BUFFER_SIZE        (32*1024*1024)
#define H264_ERROR_BUFFER_SIZE  (512)

#if (defined(__GNUC__))

#define H264_HAVE_GETOPT_LONG

#include <getopt.h>

static struct option H264_longOptions[] =
    {
        {"probe",   no_argument,       NULL, 'p'},
        {"output",  required_argument, NULL, 'o'},
        {"help",    no_argument,       NULL, 'h'},
        {"verbose", required_argument, NULL, 'v'},
    };
#endif

static char H264_options[] =
    "\t-o output_file, defaults to test.264\n"
    "\t-v verbose_level, print more info\n"
    "\t-p print codec for HTML5 video tag's codecs parameter, per RFC6381\n"
    "\t-h print this message and exit\n";

void H264_analyzerUsage(void)
{
    fprintf(stderr, "h264_analyze, version 0.2.0\n");
    fprintf(stderr, "Analyze H.264 bitstreams in Annex B format\n");
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "h264_analyze [H264_options] <input bitstream>\nH264_options:\n%s\n", H264_options);
}

int main(const int argc, char *argv[])
{
    FILE *inFile;
    uint8_t *buffer = (uint8_t *) malloc(H264_BUFFER_SIZE);
    h264_stream_t *h264Stream = h264_new();

    if (argc < 2)
    {
        H264_analyzerUsage();
        return EXIT_FAILURE;
    }

    int optVerbose = 1;
    int optProbe = 0;
    errno_t errorNum;
    char errorMsg[H264_ERROR_BUFFER_SIZE] = "";

#ifdef H264_HAVE_GETOPT_LONG
    int optionResult;
    int longOptionsIndex;

    while ((optionResult = getopt_long(argc, argv, "o:phv:", H264_longOptions, &longOptionsIndex)) != -1)
    {
        switch (optionResult)
        {
            case 'o':
            {
                if (h264_dbgfile == NULL)
                {
                    h264_dbgfile = fopen(optarg, "wt");
                }
                break;
            }

            case 'p':
            {
                optProbe = 1;
                optVerbose = 0;
                break;
            }

            case 'v':
            {
                char *reminderPtr;
                optVerbose = strtol(optarg, &reminderPtr, 0);
                break;
            }

            case 'h':
            default:
            {
                H264_analyzerUsage();
                return EXIT_FAILURE;
            }
        }
    }

    errorNum = fopen_s(&inFile, argv[optind], "rb");

#else

    errorNum = fopen_s(&inFile, argv[1], "rb");

#endif

    if (errorNum != 0)
    {
        strerror_s(errorMsg, sizeof(errorMsg), errorNum);
        fprintf(stderr, "!! Error: could not open file: %s \n", errorMsg);
        return EXIT_FAILURE;
    }

    if (h264_dbgfile == NULL)
    {
        h264_dbgfile = stdout;
    }

    size_t readCount;
    size_t fileOffset = 0;
    int64_t nalOffset = 0;
    uint8_t *bufferOffset = buffer;
    int nalStart, nalEnd;

    while (true)
    {
        readCount = fread(buffer + fileOffset, 1, H264_BUFFER_SIZE - fileOffset, inFile);
        if (readCount == 0)
        {
            if (ferror(inFile))
            {
                strerror_s(errorMsg, sizeof(errorMsg), errno);
                fprintf(stderr, "!! Error: read failed: %s \n", errorMsg);
                break;
            }

            break;
        }

        fileOffset += readCount;
        while (find_nal_unit(bufferOffset, (int) fileOffset, &nalStart, &nalEnd) > 0)
        {
            if (optVerbose > 0)
            {
                fprintf(h264_dbgfile, "!! Found NAL at offset %lld (0x%04llX), size %lld (0x%04llX) \n",
                        (long long int) (nalOffset + (bufferOffset - buffer) + nalStart),
                        (long long int) (nalOffset + (bufferOffset - buffer) + nalStart),
                        (long long int) (nalEnd - nalStart),
                        (long long int) (nalEnd - nalStart));
            }

            bufferOffset += nalStart;
            read_debug_nal_unit(h264Stream, bufferOffset, nalEnd - nalStart);
            if (optProbe && h264Stream->nal->nal_unit_type == NAL_UNIT_TYPE_SPS)
            {
                /* print codec parameter, per RFC 6381. */
                int constraintByte = h264Stream->sps->constraint_set0_flag << 7;
                constraintByte |= h264Stream->sps->constraint_set1_flag << 6;
                constraintByte |= h264Stream->sps->constraint_set2_flag << 5;
                constraintByte |= h264Stream->sps->constraint_set3_flag << 4;
                constraintByte |= h264Stream->sps->constraint_set4_flag << 3;
                constraintByte |= h264Stream->sps->constraint_set5_flag << 2;

                fprintf(h264_dbgfile, "codec: avc1.%02X%02X%02X\n",
                        h264Stream->sps->profile_idc,
                        constraintByte,
                        h264Stream->sps->level_idc);

                /* TODO: add more, move to h264_stream (?) */
                /* we've seen enough, bailing out. */
                break;
            }

            if (optVerbose > 0)
            {
                fprintf(h264_dbgfile, "XX ");
                debug_bytes(bufferOffset - 4, nalEnd - nalStart + 4 >= 16 ? 16 : nalEnd - nalStart + 4);
                /* debug_nal(h264Stream, h264Stream->nal); */
            }

            bufferOffset += (nalEnd - nalStart);
            fileOffset -= nalEnd;
        }

        /* Reading the last NAL-unit if exists */
        int restNalu = find_nal_unit(bufferOffset, (int) fileOffset, &nalStart, &nalEnd);
        if (restNalu == -1)
        {
            fprintf(h264_dbgfile, "!! Found NAL at offset %lld (0x%04llX), size %lld (0x%04llX) \n",
                    (long long int) (nalOffset + (bufferOffset - buffer) + nalStart),
                    (long long int) (nalOffset + (bufferOffset - buffer) + nalStart),
                    (long long int) (nalEnd - nalStart),
                    (long long int) (nalEnd - nalStart));
            bufferOffset += nalStart;
            read_debug_nal_unit(h264Stream, bufferOffset, nalEnd - nalStart);
        }

        /* if no NALs found in buffer, discard it */
        if (bufferOffset == buffer)
        {
            fprintf(stderr,
                    "!! Did not find any NALs between offset %lld (0x%04llX), size %lld (0x%04llX), discarding \n",
                    (long long int) nalOffset,
                    (long long int) nalOffset,
                    (long long int) nalOffset + fileOffset,
                    (long long int) nalOffset + fileOffset);

            bufferOffset = buffer + fileOffset;
            fileOffset = 0;
        }

        memmove(buffer, bufferOffset, fileOffset);
        nalOffset += bufferOffset - buffer;
        bufferOffset = buffer;
    }

    h264_free(h264Stream);
    free(buffer);

    fclose(h264_dbgfile);
    fclose(inFile);

    return EXIT_SUCCESS;
}
