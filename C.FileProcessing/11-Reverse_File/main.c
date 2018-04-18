/**
 * Displays a file in reverse order
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef CTRL_Z
#define CTRL_Z '\032'
#endif

#define SLEN   50

#ifndef OS
#define DOS    1
#define UNIX   2
#define MAC    3
#define OS     DOS
#endif

int main()
{
   char file[SLEN];
   char ch;
   FILE *fp;
   long count, last;

   puts("Enter the name of the file to be processed:");
   gets(file);
   if ((fp = fopen(file, "rb")) == NULL)
   {
      printf("Reverse can't open %s\n", file);
      exit(EXIT_FAILURE);
   }

   fseek(fp, 0L, SEEK_END);  /* go to end of file */
   last = ftell(fp);

   /* if SEEK_END not supported, use this instead
      last = 0;
      while (getc(fp) != EOF) last++; */
   for (count = last - 1; count >= 0; count--)
   {
      fseek(fp, count, SEEK_SET);  /* go backward */
      ch = getc(fp);
#if OS == DOS || OS == UNIX
      if (ch != CTRL_Z && ch != '\r')
      {
         putchar(ch);
      }
#elif OS == MAC
      putchar(ch == '\r' ? '\n' : ch);
#endif
   }

   putchar('\n');
   fclose(fp);

   return EXIT_SUCCESS;
}