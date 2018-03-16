// Fig. 9.14: fig09_14.c
// Using the # flag with conversion specifiers 
// o, x, X and any floating-point specifier
#include <stdio.h>

int main(void)
{ 
   int c = 1427; // initialize c   
   printf("%#o\n", c);
   printf("%#x\n", c);
   printf("%#X\n", c);

   double p = 1427.0; // initialize p
   printf("\n%g\n", p);
   printf("%#g\n", p);
} 
