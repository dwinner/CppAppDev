/**
 * Initializing the elements of array s to the even integers from 2 to 20
 */
#include <stdio.h>
#define SIZE 5

int main(int argc, char* argv[])
{
   int s[SIZE] = { 32, 27, 64, 18, 95 };

   for (size_t i = 0; i < SIZE; ++i)
   {
      s[i] = 2 + 2 * i;
   }

   printf("%s%13s\n", "Element", "Value");

   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%7u%13d\n", i, s[i]);
   }
}
