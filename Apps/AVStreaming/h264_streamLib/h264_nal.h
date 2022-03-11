#ifndef H264STREAMLIB_H264_NAL_H
#define H264STREAMLIB_H264_NAL_H

#include "h264_stream.h"

h264_stream_t* h264_new();

void h264_free(h264_stream_t* h);

int find_nal_unit(uint8_t* buf, int size, int* nal_start, int* nal_end);

int rbsp_to_nal(const uint8_t* rbsp_buf, const int* rbsp_size, uint8_t* nal_buf, int* nal_size);

int nal_to_rbsp(const uint8_t* nal_buf, int* nal_size, uint8_t* rbsp_buf, int* rbsp_size);

int peek_nal_unit(h264_stream_t* h, uint8_t* buf, int size);

#endif //H264STREAMLIB_H264_NAL_H
