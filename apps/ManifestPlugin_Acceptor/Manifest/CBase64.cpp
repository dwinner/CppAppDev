/************************************************
*												            *
* CBase64.cpp									         *
* Base 64 de- and encoding class				   *
*												            *
* ============================================ *
*												            *
* This class was written on 28.05.2003			*
* by Jan Raddatz [jan-raddatz@web.de]			   *
*												            *
* ============================================ *
*												            *
* Copyright (c) by Jan Raddatz					   *
* This class was published @ codeguru.com		*
* 28.05.2003								          	*
*												            *
************************************************/
#include "pch.h"
#include "CBase64.h"

CBase64::CBase64()
{
   memset(m_acEncodingBuffer, 0x00, ENC_BUFFER_SIZE);
   memset(m_acDecodingBuffer, 0x00, DEC_BUFFER_SIZE);
}


unsigned int CBase64::CalculateRecquiredEncodeOutputBufferSize(unsigned int p_InputByteCount)
{
   div_t result = div(p_InputByteCount, 3);

   unsigned int RecquiredBytes = 0;
   if (result.rem == 0)
   {
      // Number of encoded characters
      RecquiredBytes = result.quot * 4;

      // CRLF -> "\r\n" each 76 characters
      result = div(RecquiredBytes, 76);
      RecquiredBytes += result.quot * 2;

      // Terminating null for the Encoded String
      RecquiredBytes += 1;

      return RecquiredBytes;
   }
   else
   {
      // Number of encoded characters
      RecquiredBytes = result.quot * 4 + 4;

      // CRLF -> "\r\n" each 76 characters
      result = div(RecquiredBytes, 76);
      RecquiredBytes += result.quot * 2;

      // Terminating null for the Encoded String
      RecquiredBytes += 1;

      return RecquiredBytes;
   }
}

unsigned int CBase64::CalculateRecquiredDecodeOutputBufferSize(const u_char* p_pInputBufferString, u_int length)
{
   unsigned int BufferLength = length;

   div_t result = div(BufferLength, 4);

   if (p_pInputBufferString[BufferLength - 1] != '=')
   {
      return result.quot * 3;
   }
   else
   {
      if (p_pInputBufferString[BufferLength - 2] == '=')
      {
         return result.quot * 3 - 2;
      }
      else
      {
         return result.quot * 3 - 1;
      }
   }
}

unsigned int CBase64::CalculateRecquiredDecodeOutputBufferSize(const TCHAR* p_pInputBufferString)
{
   return CalculateRecquiredDecodeOutputBufferSize((const u_char*)p_pInputBufferString, _tcslen(p_pInputBufferString));
}

void CBase64::EncodeByteTriple(const TCHAR* p_pInputBuffer, unsigned int InputCharacters, TCHAR* p_pOutputBuffer)
{
   unsigned int mask = 0xfc000000;
   unsigned int buffer = 0;


   TCHAR* temp = (TCHAR*)&buffer;
   temp[3] = p_pInputBuffer[0];
   if (InputCharacters > 1)
      temp[2] = p_pInputBuffer[1];
   if (InputCharacters > 2)
      temp[1] = p_pInputBuffer[2];

   switch (InputCharacters)
   {
   case 3:
   {
      p_pOutputBuffer[0] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[1] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[2] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[3] = BASE64_ALPHABET[(buffer & mask) >> 26];
      break;
   }
   case 2:
   {
      p_pOutputBuffer[0] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[1] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[2] = BASE64_ALPHABET[(buffer & mask) >> 26];
      p_pOutputBuffer[3] = '=';
      break;
   }
   case 1:
   {
      p_pOutputBuffer[0] = BASE64_ALPHABET[(buffer & mask) >> 26];
      buffer = buffer << 6;
      p_pOutputBuffer[1] = BASE64_ALPHABET[(buffer & mask) >> 26];
      p_pOutputBuffer[2] = '=';
      p_pOutputBuffer[3] = '=';
      break;
   }
   }
}

unsigned int CBase64::DecodeByteQuartet(const TCHAR* p_pInputBuffer, TCHAR* p_pOutputBuffer)
{
   unsigned int buffer = 0;

   if (p_pInputBuffer[3] == '=')
   {
      if (p_pInputBuffer[2] == '=')
      {
         buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[0]]) << 6;
         buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[1]]) << 6;
         buffer = buffer << 14;

         TCHAR* temp = (TCHAR*)&buffer;
         p_pOutputBuffer[0] = temp[3];

         return 1;
      }
      else
      {
         buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[0]]) << 6;
         buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[1]]) << 6;
         buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[2]]) << 6;
         buffer = buffer << 8;

         TCHAR* temp = (TCHAR*)&buffer;
         p_pOutputBuffer[0] = temp[3];
         p_pOutputBuffer[1] = temp[2];

         return 2;
      }
   }
   else
   {
      buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[0]]) << 6;
      buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[1]]) << 6;
      buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[2]]) << 6;
      buffer = (buffer | BASE64_DEALPHABET[p_pInputBuffer[3]]) << 6;
      buffer = buffer << 2;

      TCHAR* temp = (TCHAR*)&buffer;
      p_pOutputBuffer[0] = temp[3];
      p_pOutputBuffer[1] = temp[2];
      p_pOutputBuffer[2] = temp[1];

      return 3;
   }
}

void CBase64::EncodeBuffer(const TCHAR* p_pInputBuffer, unsigned int p_InputBufferLength, TCHAR* p_pOutputBufferString)
{
   unsigned int FinishedByteQuartetsPerLine = 0;
   unsigned int InputBufferIndex = 0;
   unsigned int OutputBufferIndex = 0;

   memset(p_pOutputBufferString, 0, CalculateRecquiredEncodeOutputBufferSize(p_InputBufferLength));

   while (InputBufferIndex < p_InputBufferLength)
   {
      if (p_InputBufferLength - InputBufferIndex <= 2)
      {
         FinishedByteQuartetsPerLine++;
         EncodeByteTriple(p_pInputBuffer + InputBufferIndex, p_InputBufferLength - InputBufferIndex, p_pOutputBufferString + OutputBufferIndex);
         break;
      }
      else
      {
         FinishedByteQuartetsPerLine++;
         EncodeByteTriple(p_pInputBuffer + InputBufferIndex, 3, p_pOutputBufferString + OutputBufferIndex);
         InputBufferIndex += 3;
         OutputBufferIndex += 4;
      }

      if (FinishedByteQuartetsPerLine == 19)
      {
         p_pOutputBufferString[OutputBufferIndex] = '\r';
         p_pOutputBufferString[OutputBufferIndex + 1] = '\n';
         p_pOutputBufferString += 2;
         FinishedByteQuartetsPerLine = 0;
      }
   }
}

unsigned int CBase64::DecodeBuffer(const u_char* p_pInputBuffer, u_int length, u_char* p_pOutputBuffer)
{
   unsigned int InputBufferIndex = 0;
   unsigned int OutputBufferIndex = 0;
   unsigned int InputBufferLength = length;

   TCHAR ByteQuartet[4];

   while (InputBufferIndex < InputBufferLength)
   {
      for (int i = 0; i < 4; i++)
      {
         ByteQuartet[i] = p_pInputBuffer[InputBufferIndex];

         // Ignore all characters except the ones in BASE64_ALPHABET
         if ((ByteQuartet[i] >= 48 && ByteQuartet[i] <= 57) ||
            (ByteQuartet[i] >= 65 && ByteQuartet[i] <= 90) ||
            (ByteQuartet[i] >= 97 && ByteQuartet[i] <= 122) ||
            ByteQuartet[i] == '+' || ByteQuartet[i] == '/' || ByteQuartet[i] == '=')
         {
         }
         else
         {
            // Invalid character
            i--;
         }

         InputBufferIndex++;
      }

      OutputBufferIndex += DecodeByteQuartet(ByteQuartet, (TCHAR*)p_pOutputBuffer + OutputBufferIndex);
   }

   // OutputBufferIndex gives us the next position of the next decoded character
   // inside our output buffer and thus represents the number of decoded characters
   // in our buffer.
   return OutputBufferIndex;
}

unsigned int CBase64::DecodeBuffer(const TCHAR* p_pInputBufferString, TCHAR* p_pOutputBuffer)
{
   return DecodeBuffer((const u_char*)p_pInputBufferString, _tcslen(p_pInputBufferString), (u_char*)p_pOutputBuffer);
}

unsigned int CBase64::CreateMatchingEncodingBuffer(unsigned int p_InputByteCount, TCHAR** p_ppEncodingBuffer)
{
   unsigned int Size = CalculateRecquiredEncodeOutputBufferSize(p_InputByteCount);

   // Anzahl der zu verschlüsselnden Zeichen auf 32 begrenzt
   ASSERT(Size <= MAX_KEY);

   memset(m_acEncodingBuffer, 0x00, ENC_BUFFER_SIZE);
   (*p_ppEncodingBuffer) = m_acEncodingBuffer;
   return Size;
}

unsigned int CBase64::CreateMatchingDecodingBuffer(TCHAR* p_pInputBufferString, TCHAR** p_ppDecodingBuffer)
{
   unsigned int Size = CalculateRecquiredDecodeOutputBufferSize(p_pInputBufferString);

   // Anzahl der zu verschlüsselnden Zeichen auf 32 begrenzt
   ASSERT(Size <= MAX_KEY);

   memset(m_acDecodingBuffer, 0x00, DEC_BUFFER_SIZE);
   (*p_ppDecodingBuffer) = m_acDecodingBuffer;
   return Size;
}

unsigned int CBase64::EncodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pEncodedFileName)
{
   CFile InputFile;
   CFile OutputFile;

   if (!InputFile.Open(p_pSourceFileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeText))
      return UNABLE_TO_OPEN_INPUT_FILE;

   if (!OutputFile.Open(p_pEncodedFileName, CFile::modeCreate | CFile::modeWrite))
      return UNABLE_TO_OPEN_OUTPUT_FILE;

   TCHAR InputBuffer[19 * 3];
   TCHAR* pOutputBuffer;
   CreateMatchingEncodingBuffer(sizeof(InputBuffer), &pOutputBuffer);

   if (pOutputBuffer == 0)
      return UNABLE_TO_CREATE_OUTPUTBUFFER;

   unsigned int ReadBytes = 0;
   while ((ReadBytes = InputFile.Read(InputBuffer, sizeof(InputBuffer))) != 0)
   {
      EncodeBuffer(InputBuffer, ReadBytes, pOutputBuffer);
      OutputFile.Write(pOutputBuffer, _tcslen(pOutputBuffer));
   }

   OutputFile.Flush();
   OutputFile.Close();
   InputFile.Close();

   return 0;
}

unsigned int CBase64::DecodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pDecodedFileName)
{
   CStdioFile	InputFile;
   CFile		OutputFile;

   if (!InputFile.Open(p_pSourceFileName, CFile::modeRead))
      return UNABLE_TO_OPEN_INPUT_FILE;

   if (!OutputFile.Open(p_pDecodedFileName, CFile::modeCreate | CFile::modeWrite))
      return UNABLE_TO_OPEN_OUTPUT_FILE;

   CString InputBuffer;
   TCHAR	OutputBuffer[64];

   unsigned int ReadBytes = 0;
   while ((ReadBytes = InputFile.ReadString(InputBuffer)) != 0)
   {
      InputBuffer.Remove('\r');
      InputBuffer.Remove('\n');
      unsigned int DecodedBytes = DecodeBuffer(InputBuffer.GetBuffer(), OutputBuffer);
      OutputFile.Write(&OutputBuffer[0], DecodedBytes);
   }


   OutputFile.Flush();
   OutputFile.Close();
   InputFile.Close();

   return 0;
}
