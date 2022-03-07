#include "h264_read_frame.h"

int init()
{
   if (g_cache[0] == NULL)
   {
      g_cache[0] = (uint8_t *) malloc(CACHE_LEN);
   }

   if (g_cache[1] == NULL)
   {
      g_cache[1] = (uint8_t *) malloc(CACHE_LEN);
   }

   if (fp_inH264 == NULL)
   {
      fp_inH264 = fopen("./test.h264", "r");
      if (fp_inH264 == NULL)
      {
         printf("fopen erro [%d%s]\n", __LINE__, __FUNCTION__);
         return EXIT_FAILURE;
      }
   }

   if (fread(g_cache[iCache], 1, CACHE_LEN, fp_inH264) < CACHE_LEN)
   {
      printf("Input file too short [%d%s]\n", __LINE__, __FUNCTION__);
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

int deInit()
{
   if (g_cache[0])
   {
      free(g_cache[0]);
      g_cache[0] = NULL;
   }

   if (g_cache[1])
   {
      free(g_cache[1]);
      g_cache[1] = NULL;
   }

   if (fp_inH264)
   {
      fclose(fp_inH264);
      fp_inH264 = NULL;
   }

   return EXIT_SUCCESS;
}

int checkHead(uint8_t *buffer, int offset)
{
   static uint8_t mMark[4] = {0x00, 0x00, 0x00, 0x01};
   return !memcmp(buffer + offset, mMark, 4);
}

int getOneFrame(uint8_t *buffer, int bufferLen)
{
   int i;
   int startPoint = iOffset;
   int endPoint = iOffset;
   for (i = iOffset + 4; i <= CACHE_LEN - 4; i++)
   {
      if (checkHead(g_cache[iCache], i))
      {
         startPoint = iOffset;
         endPoint = i;
      }
   }

   if (endPoint - startPoint > 0)
   {
      memcpy(buffer, g_cache[iCache] + startPoint, (endPoint - startPoint));
      iOffset = endPoint;
      return endPoint - startPoint;
   }
   else
   {
      int oldLen = CACHE_LEN - startPoint;
      memcpy(g_cache[(iCache + 1) % 2], g_cache[iCache] + startPoint, oldLen);
      int newLen;
      newLen = (int) fread(g_cache[(iCache + 1) % 2] + oldLen, 1, CACHE_LEN - (oldLen), fp_inH264);
      if (newLen < CACHE_LEN - (oldLen))
      {
         return EXIT_FAILURE;
      }

      iOffset = 0;
      iCache = (iCache + 1) % 2;

      return getOneFrame(buffer, bufferLen);
   }
}
