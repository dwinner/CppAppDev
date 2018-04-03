// Fig. E.2: figE_02.c
// Assigning elements of an array prior to C99
#include <stdio.h>

int main(void)
{
   int a[5]; // array declaration 

   a[0] = 1; // explicitly assign values to array elements... 
   a[4] = 2; // after declaration of array 

   // assign zero to all elements but the first and last 
   for (size_t i = 1; i < 4; ++i) {
      a[i] = 0;
   }  

   // output array contents 
   printf("The array is\n");

   for (size_t i = 0; i < 5; ++i) {
      printf("%d\n", a[i]);
   }  
}  
