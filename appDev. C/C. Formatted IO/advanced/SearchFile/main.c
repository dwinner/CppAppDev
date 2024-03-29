/**
 * Write to stdout all the lines containing the specified search
 * string in the file opened for reading as fpIn.
 * Return value: The number of lines containing the search string, or -1 on error.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchFile(FILE *fpIn, const char *keyword);

int main()
{
   char *file = "searchFile.c";
   char pattern[256] = "";
   int count = 0;

   FILE *fp = fopen(file, "r");    // Open to read.
   if (fp == NULL)                       // Did fopen() succeed?
   {
      fprintf(stderr, "Error on opening input file \"%s\".\n", file);
      return EXIT_FAILURE;
   }

   printf("File: \"%s\".\n", file);
   printf("Search string: ");
   gets(pattern);

   if ((count = searchFile(fp, pattern)) < 0)
   {
      fprintf(stderr, "Error reading.\n");
   }
   else if (count == 0)
   {
      fprintf(stderr, "Search string not found!\n");
   }
   else
   {
      fprintf(stderr, "\n--------------\n%d lines found.\n", count);
   }

   fclose(fp);

   return EXIT_SUCCESS;
}

int searchFile(FILE *fpIn, const char *keyword)
{
#ifndef MAX_LINE
#define MAX_LINE 256
#endif

   char line[MAX_LINE] = "";
   int count = 0;

   if (fpIn == NULL || keyword == NULL)
   {
      return -1;
   }
   else
   {
      rewind(fpIn);
   }

   while (fgets(line, MAX_LINE, fpIn) != NULL)
   {
      if (strstr(line, keyword) != NULL)
      {
         ++count;
         fputs(line, stdout);
      }
   }

   return !feof(fpIn) ? -1 : count;
}
