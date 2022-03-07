/**
 * H264 test file - reading frame alone h.264 files from the C language version
 */

#include <stdio.h>
#include <stdlib.h>
#include "h264_read_frame.h"

int main()
{
   if (init())
   {
      return EXIT_FAILURE;
   }

   uint8_t *buffer = (uint8_t *) malloc(CACHE_LEN);
   int len;
   FILE *fpOut = fopen("out.h264", "w+");
   while ((len = getOneFrame(buffer, CACHE_LEN)) > 0)
   {
      printf("get a frame: %d\n", len);
      fwrite(buffer, 1, len, fpOut);
   }

   fclose(fpOut);
   free(buffer);
   deInit();

   return EXIT_SUCCESS;
}
