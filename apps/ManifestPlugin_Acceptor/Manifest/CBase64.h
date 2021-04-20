#pragma once

#include <afx.h>

constexpr auto DecBufferSize = 64;
constexpr auto EncBufferSize = 64;
constexpr auto MaxKey = 32;
const static unsigned int MaxLineLength = 76;

const static char Base64Alphabet[64] =
{
   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', //   0 -   9
   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', //  10 -  19
   'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', //  20 -  29
   'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', //  30 -  39
   'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', //  40 -  49
   'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', //  50 -  59
   '8', '9', '+', '/' //  60 -  63
};

const static char Base64Dealphabet[128] =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //   0 -   9
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  10 -  19
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  20 -  29
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //  30 -  39
   0, 0, 0, 62, 0, 0, 0, 63, 52, 53, //  40 -  49
   54, 55, 56, 57, 58, 59, 60, 61, 0, 0, //  50 -  59
   0, 61, 0, 0, 0, 0, 1, 2, 3, 4, //  60 -  69
   5, 6, 7, 8, 9, 10, 11, 12, 13, 14, //  70 -  79
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, //  80 -  89
   25, 0, 0, 0, 0, 0, 0, 26, 27, 28, //  90 -  99
   29, 30, 31, 32, 33, 34, 35, 36, 37, 38, // 100 - 109
   39, 40, 41, 42, 43, 44, 45, 46, 47, 48, // 110 - 119
   49, 50, 51, 0, 0, 0, 0, 0 // 120 - 127
};

enum
{
   unable_to_open_input_file,
   unable_to_open_output_file,
   unable_to_create_outputbuffer
};

class CBase64
{
public:
   CBase64();

   ~CBase64() = default;   

   unsigned int CalculateRecquiredEncodeOutputBufferSize(unsigned int p_inputByteCount) const;

   unsigned int CalculateRecquiredDecodeOutputBufferSize(const TCHAR* p_pInputBufferString) const;

   unsigned int CalculateRecquiredDecodeOutputBufferSize(const u_char* p_pInputBufferString, u_int length) const;

   static void EncodeByteTriple(const TCHAR* p_pInputBuffer, unsigned int inputCharacters, TCHAR* p_pOutputBuffer);

   static unsigned int DecodeByteQuartet(const TCHAR* p_pInputBuffer, TCHAR* p_pOutputBuffer);

   void EncodeBuffer(const TCHAR* p_pInputBuffer, unsigned int p_inputBufferLength, TCHAR* p_pOutputBufferString) const;

   unsigned int DecodeBuffer(const TCHAR* p_pInputBufferString, TCHAR* p_pOutputBuffer) const;

   static unsigned int DecodeBuffer(const u_char* p_pInputBuffer, u_int length, u_char* p_pOutputBuffer);

   unsigned int CreateMatchingEncodingBuffer(unsigned int p_inputByteCount, TCHAR** p_ppEncodingBuffer);

   unsigned int CreateMatchingDecodingBuffer(TCHAR* p_pInputBufferString, TCHAR** p_ppDecodingBuffer);

   unsigned int EncodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pEncodedFileName);

   unsigned int DecodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pDecodedFileName) const;

protected:

   TCHAR acDecodingBuffer_[DecBufferSize]{};
   TCHAR acEncodingBuffer_[EncBufferSize]{};
};
