/**
 * Using the p and % conversion specifiers
 */
#include <stdio.h>

int main(void)
{
   int x = 12345; // initialize int x
   int* ptr = &x; // assign address of x to ptr

   printf("The value of ptr is %p\n", ptr);
   printf("The address of x is %p\n\n", &x);

   printf("Printing a %% in a format control string\n");

   return 0;
}
