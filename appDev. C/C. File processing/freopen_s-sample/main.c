// freopen_s_ex.c : freopen_s() example
// -------------------------------------------------------------
// errno_t freopen_s(   FILE * restrict * restrict fpPtr,
//                      const char * restrict name,
//                      const char * restrict mode,
//                      FILE * restrict fp );

#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()      // Redirect standard output to the file redirect.txt:
{
   char filename[] = "redirect.txt";
   FILE *fp;

   errno_t err = freopen_s(&fp, filename, "w", stdout);
   if (err != 0)
   {
      fprintf(stderr, "Unable to redirect stdout to %s\n", filename);
      exit(err);
   }

   printf("This text is being written to the file %s.\n", filename);

   fclose(stdout);

   return 0;
}
