/**
 * The function isReadWriteable() tests whether the file exists and
 * may be opened for reading and writing access.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isReadWriteable(const char *fileName);

int main()
{
   char *fileName = "isReadWriteable.c";

   if (isReadWriteable(fileName))
   {
      printf("The file \"%s\" may be opened for read and write operations.\n",
             fileName);
   }
   else
   {
      printf("The file \"%s\" does not exist or can not be opened "
             "for reading and writing.\n", fileName);
   }

   return EXIT_SUCCESS;
}

bool isReadWriteable(const char *fileName)
{
   FILE *fp = fopen(fileName, "r+");      // Open a file to read and write.

   if (fp != NULL)  // Did fopen() succeed?
   {
      fclose(fp); // Yes: close the file; no error handling.
      return true;
   }
   else  // No.
   {
      return false;
   }
}
