/**
 * Using implicit int prior to C99
 */

#include <stdio.h>

returnImplicitInt(); // prototype with unspecified return type 
int demoImplicitInt(x); // prototype missing a parameter name type 

int main(void)
{
   // assign data of unspecified return type to int 
   int x = returnImplicitInt();

   // pass in an int to a function with an unspecified type 
   int y = demoImplicitInt(82);

   printf("x is %d\n", x);
   printf("y is %d\n", y);

   return 0;
}

returnImplicitInt()
{
   return 77; // returning an int when return type is not specified 
}

int demoImplicitInt(x)
{
   return x;
} 
