// Example 9-1. Dereferencing a pointer
// dereferencing.c

#include <stdio.h>

int main()
{
   double x, y, *ptr;       // Two double variables and a pointer to double.
   ptr = &x;                // Let ptr point to x.
   *ptr = 7.8;              // Assign the value 7.8 to the variable x.
   printf("x = %6.2f\n", x);
   *ptr *= 2.5;             // Multiply x by 2.5.
   printf("x = %6.2f\n", x);
   y = *ptr + 0.5;          // Assign y the result of the addition x + 0.5.
   printf("y = %6.2f\n", y);

   return 0;
}

