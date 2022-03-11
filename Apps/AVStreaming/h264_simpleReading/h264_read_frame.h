#ifndef READINGH264FRAME_H264_READ_FRAME_H
#define READINGH264FRAME_H264_READ_FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef unsigned char uint8_t;   // Unsigned 8-bit

/**
 * Buffer can not be set too small, if the ratio appears greater than a frame buffer, will be overwritten part
 */
#define CACHE_LEN (1024 * 500)

static uint8_t *g_cache[2] = {NULL, NULL};

static FILE *fp_inH264 = NULL;

static int iCache = 0;

static int iOffset = 0;

/**
 * Init
 * @return Success code
 */
int init();

/**
 * De init
 * @return Success code
 */
int deInit();

/**
 * Check H.264 head data
 * @param buffer Buffer
 * @param offset Buffer offset
 * @return True if it's not a H.264 head, False otherwise
 */
int checkHead(uint8_t *buffer, int offset);

/**
 * Get a data buffer
 * @param buffer Data indicating the maximum buffer can accomodate
 * @param bufferLen buffer length
 * @return The actual length of the data frame
 */
int getOneFrame(uint8_t *buffer, int bufferLen);

#endif //READINGH264FRAME_H264_READ_FRAME_H
