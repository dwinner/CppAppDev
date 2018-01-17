/**
 * Applying sizeof to an array name returns
 * the number of bytes in the array
 */
#include <stdio.h>

#define SIZE 20

size_t getSize(const float* ptr);

int main()
{
   float array[SIZE]; // create array
   printf("The number of bytes in the array is %u"
          "\nThe number of bytes returned by getSize is %u\n",
          sizeof array, getSize(array));

   return 0;
}

size_t getSize(const float* ptr)
{
   return sizeof ptr;
}
