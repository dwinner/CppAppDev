/**
 * Initializing the elements of an array to zeros
 */
#include <stdio.h>

int main(void)
{
   int n[5];

   for (size_t i = 0; i < 5; ++i)
   {
      n[i] = 0;
   }

   printf("%s%13s\n", "Element", "Value");

   for (size_t i = 0; i < 5; ++i)
   {
      printf("%7u%13d", i, n[i]);
   }
}
