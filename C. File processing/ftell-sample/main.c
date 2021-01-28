// ftell_ex.c : ftell() example
// -------------------------------------------------------------
// This example searches in a file, whose name is the second command-line
// argument, for a string, which the user can specify in the first
// command-line argument.
// long ftell( FILE *fp );

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

int main(int argc, char *argv[])
{
   FILE *fp;
   long lOffset = 0L;
   char sLine[MAX_LINE] = "";
   int lineno = 0;

   if (argc != 3)
   {
      fprintf(stderr, "Usage: program search_string file_name\n"), exit(1);
   }

   if ((fp = fopen(argv[2], "r")) == NULL)
   {
      fprintf(stderr, "Unable to open file %s\n", argv[2]);
      exit(-1);
   }

   do
   {
      // Bookmark the beginning of the line we're about to read.
      lOffset = ftell(fp);
      if (-1L == lOffset)
      {
         fprintf(stderr, "Unable to obtain offset in %s\n", argv[2]);
      }
      else
      {
         lineno++;
      }

      // Read next line from file.
      if (!fgets(sLine, MAX_LINE, fp))
      {
         break;
      }
   }
   while (strstr(sLine, argv[1]) == NULL);    // Test for argument in sLine.

   /* Dropped out of loop: Found search keyword or EOF */
   if (feof(fp) || ferror(fp))
   {
      fprintf(stderr, "Unable to find \"%s\" in %s\n", argv[1], argv[2]);
      rewind(fp);
   }
   else
   {
      printf("%s (%d): %s\n", argv[2], lineno, sLine);
      fseek(fp, lOffset, 0); // Set file pointer at beginning of
      // the line containing the keyword
   }

   return 0;
}
