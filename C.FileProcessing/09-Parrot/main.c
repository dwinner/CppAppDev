/**
 * Using fgets() and fputs()
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 20

int main(void)
{
   char line[MAXLINE];

   while (fgets(line, MAXLINE, stdin) != NULL && line[0] != '\n')
      fputs(line, stdout);

   return EXIT_SUCCESS;
}
