#include "parser_utils.h"
#include <stdio.h>
#include <setjmp.h>

void sntx_err(int error)
{
   char *p, *temp;
   int linecount = 0;
   register int i;

   static char *e[] =
      {
         "syntax error",
         "unbalanced parentheses",
         "no expression present",
         "equals sign expected",
         "not a variable",
         "parameter error",
         "semicolon expected",
         "unbalanced braces",
         "function undefined",
         "type specifier expected",
         "too many nested function calls",
         "return without call",
         "parentheses expected",
         "while expected",
         "closing quote expected",
         "not a string",
         "too many local variables",
         "division by zero"
      };

   printf("\n%s", e[error]);

   p = p_buf;

   // find line number of error
   while (p != prog)
   {
      p++;
      if (*p == '\r')
      {
         linecount++;
      }
   }

   printf(" in line %d\n", linecount);

   temp = p;
   for (i = 0; i < 20 && p > p_buf && *p != '\n'; i++, p--);
   for (i = 0; i < 30 && p <= temp; i++, p++)
   {
      printf("%c", *p);
   }

   longjmp(e_buf, 1); /* return to safe point */
}
