/**
 * Using the # flag with conversion specifiers o, x, X
 * and any floating-point specifier
 */
#include <stdio.h>

int main(void)
{
   const int c = 1427; // initialize c   
   printf("%#o\n", c);
   printf("%#x\n", c);
   printf("%#X\n", c);

   const double p = 1427.0; // initialize p
   printf("\n%g\n", p);
   printf("%#g\n", p);

   return 0;
}
