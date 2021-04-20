#include "pch.h"
#include "CBase64.h"

CBase64::CBase64()
{
   memset(acEncodingBuffer_, 0x00, EncBufferSize);
   memset(acDecodingBuffer_, 0x00, DecBufferSize);
}

unsigned int CBase64::CalculateRecquiredEncodeOutputBufferSize(const unsigned int p_inputByteCount) const
{
   auto result = div(static_cast<int>(p_inputByteCount), 3);

   unsigned int recquiredBytes = 0;
   if (result.rem == 0)
   {
      // Number of encoded characters
      recquiredBytes = result.quot * 4;

      // CRLF -> "\r\n" each 76 characters
      result = div(static_cast<int>(recquiredBytes), 76);
      recquiredBytes += result.quot * 2;

      // Terminating null for the Encoded String
      recquiredBytes += 1;

      return recquiredBytes;
   }

   // Number of encoded characters
   recquiredBytes = result.quot * 4 + 4;

   // CRLF -> "\r\n" each 76 characters
   result = div(static_cast<int>(recquiredBytes), 76);
   recquiredBytes += result.quot * 2;

   // Terminating null for the Encoded String
   recquiredBytes += 1;

   return recquiredBytes;
}

unsigned int CBase64::CalculateRecquiredDecodeOutputBufferSize(const u_char* p_pInputBufferString,
                                                               const u_int length) const
{
   const unsigned int bufferLength = length;
   const div_t result = div(static_cast<int>(bufferLength), 4);

   return p_pInputBufferString[bufferLength - 1] != '='
             ? result.quot * 3
             : result.quot * 3 - (p_pInputBufferString[bufferLength - 2] != '='
                                     ? 1
                                     : 2);
}

unsigned int CBase64::CalculateRecquiredDecodeOutputBufferSize(const TCHAR* p_pInputBufferString) const
{
   return CalculateRecquiredDecodeOutputBufferSize(reinterpret_cast<const u_char*>(p_pInputBufferString),
                                                   _tcslen(p_pInputBufferString));
}

void CBase64::EncodeByteTriple(const TCHAR* p_pInputBuffer, unsigned int inputCharacters, TCHAR* p_pOutputBuffer)
{
   const unsigned int mask = 0xfc000000;
   unsigned int buffer = 0;

   auto* const temp = reinterpret_cast<TCHAR*>(&buffer);
   temp[3] = p_pInputBuffer[0];
   if (inputCharacters > 1)
   {
      temp[2] = p_pInputBuffer[1];
   }

   if (inputCharacters > 2)
   {
      temp[1] = p_pInputBuffer[2];
   }

   switch (inputCharacters)
   {
   case 3:
      {
         p_pOutputBuffer[0] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[1] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[2] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[3] = Base64Alphabet[(buffer & mask) >> 26];
         break;
      }
   case 2:
      {
         p_pOutputBuffer[0] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[1] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[2] = Base64Alphabet[(buffer & mask) >> 26];
         p_pOutputBuffer[3] = '=';
         break;
      }
   case 1:
      {
         p_pOutputBuffer[0] = Base64Alphabet[(buffer & mask) >> 26];
         buffer = buffer << 6;
         p_pOutputBuffer[1] = Base64Alphabet[(buffer & mask) >> 26];
         p_pOutputBuffer[2] = '=';
         p_pOutputBuffer[3] = '=';
         break;
      }

   default:
      break;
   }
}

unsigned int CBase64::DecodeByteQuartet(const TCHAR* p_pInputBuffer, TCHAR* p_pOutputBuffer)
{
   unsigned int buffer = 0;

   if (p_pInputBuffer[3] == '=')
   {
      if (p_pInputBuffer[2] == '=')
      {
         buffer = (buffer | Base64Dealphabet[p_pInputBuffer[0]]) << 6;
         buffer = (buffer | Base64Dealphabet[p_pInputBuffer[1]]) << 6;
         buffer = buffer << 14;

         auto* const temp = reinterpret_cast<TCHAR*>(&buffer);
         p_pOutputBuffer[0] = temp[3];

         return 1;
      }

      buffer = (buffer | Base64Dealphabet[p_pInputBuffer[0]]) << 6;
      buffer = (buffer | Base64Dealphabet[p_pInputBuffer[1]]) << 6;
      buffer = (buffer | Base64Dealphabet[p_pInputBuffer[2]]) << 6;
      buffer = buffer << 8;

      auto* const temp = reinterpret_cast<TCHAR*>(&buffer);
      p_pOutputBuffer[0] = temp[3];
      p_pOutputBuffer[1] = temp[2];

      return 2;
   }

   buffer = (buffer | Base64Dealphabet[p_pInputBuffer[0]]) << 6;
   buffer = (buffer | Base64Dealphabet[p_pInputBuffer[1]]) << 6;
   buffer = (buffer | Base64Dealphabet[p_pInputBuffer[2]]) << 6;
   buffer = (buffer | Base64Dealphabet[p_pInputBuffer[3]]) << 6;
   buffer = buffer << 2;

   auto* const temp = reinterpret_cast<TCHAR*>(&buffer);
   p_pOutputBuffer[0] = temp[3];
   p_pOutputBuffer[1] = temp[2];
   p_pOutputBuffer[2] = temp[1];

   return 3;
}

void CBase64::EncodeBuffer(const TCHAR* p_pInputBuffer, const unsigned int p_inputBufferLength,
                           TCHAR* p_pOutputBufferString) const
{
   unsigned int finishedByteQuartetsPerLine = 0;
   unsigned int inputBufferIndex = 0;
   unsigned int outputBufferIndex = 0;

   memset(p_pOutputBufferString, 0, CalculateRecquiredEncodeOutputBufferSize(p_inputBufferLength));

   while (inputBufferIndex < p_inputBufferLength)
   {
      if (p_inputBufferLength - inputBufferIndex <= 2)
      {
         finishedByteQuartetsPerLine++;
         EncodeByteTriple(p_pInputBuffer + inputBufferIndex, p_inputBufferLength - inputBufferIndex,
                          p_pOutputBufferString + outputBufferIndex);
         break;
      }

      finishedByteQuartetsPerLine++;
      EncodeByteTriple(p_pInputBuffer + inputBufferIndex, 3, p_pOutputBufferString + outputBufferIndex);
      inputBufferIndex += 3;
      outputBufferIndex += 4;

      if (finishedByteQuartetsPerLine == 19)
      {
         p_pOutputBufferString[outputBufferIndex] = '\r';
         p_pOutputBufferString[outputBufferIndex + 1] = '\n';
         p_pOutputBufferString += 2;
         finishedByteQuartetsPerLine = 0;
      }
   }
}

unsigned int CBase64::DecodeBuffer(const u_char* p_pInputBuffer, const u_int length, u_char* p_pOutputBuffer)
{
   unsigned int inputBufferIndex = 0;
   unsigned int outputBufferIndex = 0;
   const unsigned int InputBufferLength = length;

   TCHAR byteQuartet[4];

   while (inputBufferIndex < InputBufferLength)
   {
      for (int i = 0; i < 4; i++)
      {
         byteQuartet[i] = p_pInputBuffer[inputBufferIndex];

         // Ignore all characters except the ones in BASE64_ALPHABET
         if (byteQuartet[i] >= 48 && byteQuartet[i] <= 57 ||
            byteQuartet[i] >= 65 && byteQuartet[i] <= 90 ||
            byteQuartet[i] >= 97 && byteQuartet[i] <= 122 ||
            byteQuartet[i] == '+' || byteQuartet[i] == '/' || byteQuartet[i] == '=')
         {
         }
         else
         {
            // Invalid character
            i--;
         }

         inputBufferIndex++;
      }

      outputBufferIndex += DecodeByteQuartet(byteQuartet,
                                             reinterpret_cast<TCHAR*>(p_pOutputBuffer) + outputBufferIndex);
   }

   // OutputBufferIndex gives us the next position of the next decoded character
   // inside our output buffer and thus represents the number of decoded characters
   // in our buffer.
   return outputBufferIndex;
}

unsigned int CBase64::DecodeBuffer(const TCHAR* p_pInputBufferString, TCHAR* p_pOutputBuffer) const
{
   return DecodeBuffer(reinterpret_cast<const u_char*>(p_pInputBufferString), _tcslen(p_pInputBufferString),
                       reinterpret_cast<u_char*>(p_pOutputBuffer));
}

unsigned int CBase64::CreateMatchingEncodingBuffer(const unsigned int p_inputByteCount, TCHAR** p_ppEncodingBuffer)
{
   const auto size = CalculateRecquiredEncodeOutputBufferSize(p_inputByteCount);

   // Anzahl der zu verschlüsselnden Zeichen auf 32 begrenzt
   ASSERT(size <= MaxKey);

   memset(acEncodingBuffer_, 0x00, EncBufferSize);
   *p_ppEncodingBuffer = acEncodingBuffer_;

   return size;
}

unsigned int CBase64::CreateMatchingDecodingBuffer(TCHAR* p_pInputBufferString, TCHAR** p_ppDecodingBuffer)
{
   const auto size = CalculateRecquiredDecodeOutputBufferSize(p_pInputBufferString);

   // Anzahl der zu verschlüsselnden Zeichen auf 32 begrenzt
   ASSERT(size <= MaxKey);

   memset(acDecodingBuffer_, 0x00, DecBufferSize);
   *p_ppDecodingBuffer = acDecodingBuffer_;

   return size;
}

unsigned int CBase64::EncodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pEncodedFileName)
{
   CFile inputFile;
   CFile outputFile;

   if (!inputFile.Open(p_pSourceFileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeText))
   {
      return unable_to_open_input_file;
   }

   if (!outputFile.Open(p_pEncodedFileName, CFile::modeCreate | CFile::modeWrite))
   {
      return unable_to_open_output_file;
   }

   TCHAR inputBuffer[19 * 3];
   TCHAR* pOutputBuffer = nullptr;
   CreateMatchingEncodingBuffer(sizeof inputBuffer, &pOutputBuffer);

   if (pOutputBuffer == nullptr)
   {
      return unable_to_create_outputbuffer;
   }

   unsigned int readBytes = 0;
   while ((readBytes = inputFile.Read(inputBuffer, sizeof(inputBuffer))) != 0)
   {
      EncodeBuffer(inputBuffer, readBytes, pOutputBuffer);
      outputFile.Write(pOutputBuffer, _tcslen(pOutputBuffer));
   }

   outputFile.Flush();
   outputFile.Close();
   inputFile.Close();

   return 0;
}

unsigned int CBase64::DecodeFile(TCHAR* p_pSourceFileName, TCHAR* p_pDecodedFileName) const
{
   CStdioFile inputFile;
   CFile outputFile;

   if (!inputFile.Open(p_pSourceFileName, CFile::modeRead))
   {
      return unable_to_open_input_file;
   }

   if (!outputFile.Open(p_pDecodedFileName, CFile::modeCreate | CFile::modeWrite))
   {
      return unable_to_open_output_file;
   }

   CString inputBuffer;
   TCHAR outputBuffer[64];

   unsigned int readBytes = 0;
   while ((readBytes = inputFile.ReadString(inputBuffer)) != 0)
   {
      inputBuffer.Remove('\r');
      inputBuffer.Remove('\n');
      const auto decodedBytes = DecodeBuffer(inputBuffer.GetBuffer(), outputBuffer);
      outputFile.Write(&outputBuffer[0], decodedBytes);
   }

   outputFile.Flush();
   outputFile.Close();
   inputFile.Close();

   return 0;
}
