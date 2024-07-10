// ungetc_ex.c : ungetc() example
// -------------------------------------------------------------
// int ungetc( int c, FILE *fp );

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
   char file[] = "unget_input.dat";
   FILE *fp;
   int inChar;
   char numstr[64];

   if ((fp = fopen(file, "r")) == NULL)
   {
      fprintf(stderr, "Can't read the file %s\n", file), exit(1);
   }

   while ((inChar = getc(fp)) != EOF)
   {
      if (isdigit(inChar))              // Collect a sequence of digits.
      {
         int i = 0;
         do
         {
            numstr[i++] = (char) inChar;
            inChar = getc(fp);
         }
         while (isdigit(inChar) && i + 1 < sizeof(numstr));

         numstr[i] = '\0';            // Terminate the numeral string.

         /* ... process the numeral string ... */
         puts(numstr);

         if (ungetc(inChar, fp) == EOF)
         {  // Put back the first non-digit.
            break;
         }

         continue;
      }

      /* ... process any non-digit characters ... */
   }

   if (!feof(fp))
   {
      fprintf(stderr, "Error processing the file %s\n", file);
   }

   return 0;
}
