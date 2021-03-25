// tmpnam_ex.c : tmpnam(), tmpnam_s() example
// -------------------------------------------------------------
// char *tmpnam( char *s );
// errno_t tmpnam_s(char *s, rsize_t maxsize);

#include <stdio.h>
#include <errno.h>

int main()
{
   char fname[L_tmpnam];   // or char fname[L_tmpnam_s];
   FILE *fpOut;

   if (tmpnam(fname) == NULL) // or if( tmpnam_s( fname, sizeof(fname)) != 0)
   {
      fputs("Error generating a temporary file name.", stderr);
      return -1;
   }

   fpOut = fopen(fname, "w+");

   fputs("... write and edit something in the file ...\n", fpOut);
   fclose(fpOut);
   printf("The results have been saved in %s.\n", fname);

   return 0;
}
