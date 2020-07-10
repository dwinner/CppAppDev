/**
 * Word counter
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
   int totalChars = 0; /* кол-во символов */
   int totalLines = 0; /* кол-во строк */
   int totalWords = 0; /* кол-во слов */
   int inSpace = 1;
   int c, last = '\n';

   while ((c = getchar()) != EOF)
   {
      last = c;
      totalChars++;
      if (isspace(c))
      {
         inSpace = 1;
         if (c == '\n')
         {
            totalLines++;
         }
      }
      else
      {
         totalWords += inSpace;
         inSpace = 0;
      }
   }

   if (last != '\n')
   {
      totalLines++;
   }

   printf("Строк, Слов, Символов\n");
   printf(" %3d %3d %3d\n", totalLines, totalWords, totalChars);

   return EXIT_SUCCESS;
}