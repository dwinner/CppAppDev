/**
 * Appends files to a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE  1024
#define SLEN      81

void append(FILE *source, FILE *dest);

int main()
{
   FILE *ptrFileToAppend, *ptrSourceFile;  // ptrFileToAppend - for append file, ptrSourceFile - for source file
   int files = 0;   // number of files appended
   char appendFileName[SLEN];  // name of append file
   char sourceFileName[SLEN];  // name of source file
   puts("Enter name of destination file:");
   gets(appendFileName);

   if ((ptrFileToAppend = fopen(appendFileName, "a")) == NULL)
   {
      fprintf(stderr, "Can't open %s\n", appendFileName);
      exit(2);
   }

   if (setvbuf(ptrFileToAppend, NULL, _IOFBF, BUF_SIZE) != 0)
   {
      fputs("Can't create output buffer\n", stderr);
      exit(3);
   }

   puts("Enter name of the first source file (empty line to quit):");

   while (gets(sourceFileName) && sourceFileName[0] != '\0')
   {
      if (strcmp(sourceFileName, appendFileName) == 0)
      {
         fputs("Can't append file to itself\n", stderr);
      }
      else if ((ptrSourceFile = fopen(sourceFileName, "r")) == NULL)
      {
         fprintf(stderr, "Can't open %s\n", sourceFileName);
      }
      else
      {
         if (setvbuf(ptrSourceFile, NULL, _IOFBF, BUF_SIZE) != 0)
         {
            fputs("Can't create input buffer\n", stderr);
            continue;
         }

         append(ptrSourceFile, ptrFileToAppend);
         if (ferror(ptrSourceFile) != 0)
         {
            fprintf(stderr, "Error in reading file %s.\n", sourceFileName);
         }

         if (ferror(ptrFileToAppend) != 0)
         {
            fprintf(stderr, "Error in writing file %s.\n", appendFileName);
         }

         fclose(ptrSourceFile);
         files++;
         printf("File %s appended.\n", sourceFileName);
         puts("Next file (empty line to quit):");
      }
   }

   printf("Done. %d files appended.\n", files);
   fclose(ptrFileToAppend);

   return EXIT_SUCCESS;
}

void append(FILE *source, FILE *dest)
{
   size_t bytes;
   static char temp[BUF_SIZE];   // allocate once

   while ((bytes = fread(temp, sizeof(char), BUF_SIZE, source)) > 0)
   {
      fwrite(temp, sizeof(char), bytes, dest);
   }
}
