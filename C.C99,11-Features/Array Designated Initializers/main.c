/**
 * Using designated initializers
 * to initialize the elements of an
 * array in С99
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
   int a[5] =
      {
         [0]=1,
         [4]=2
      };
   printf("The array is \n");
   for (size_t i = 0; i < 5; ++i)
      printf("%d\n", a[i]);

   return EXIT_SUCCESS;
}