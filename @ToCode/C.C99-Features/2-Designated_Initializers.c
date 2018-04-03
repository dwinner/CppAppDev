// Fig. E.3: figE_03.c
// Using designated initializers
// to initialze the elements of an array in C99
#include <stdio.h>

int main(void)
{
   int a[5] =
   {
      [0] = 1, // initialize elements with designated initializers
      [4] = 2 // within the declaration of the array
   };

   // output array contents
   printf("The array is \n");

   for (size_t i = 0; i < 5; ++i) {
      printf("%d\n", a[i]);
   } 
} 
