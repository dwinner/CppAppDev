/**
 * Linear search of an array
 */

#include <stdio.h>
#define  SIZE 100

// function prototype
size_t linearSearch(const int array[], const int key, const size_t size);

int main(void)
{
   int a[SIZE]; // create array a

   // create some data
   for (size_t x = 0; x < SIZE; ++x)
   {
      a[x] = 2 * x;
   }

   printf("Enter integer search key: ");
   int searchKey; // value to locate in array a
   scanf_s("%d", &searchKey);

   // attempt to locate searchKey in array a 
   const size_t index = linearSearch(a, searchKey, SIZE);

   // display results
   if (index != -1)
   {
      printf("Found value at index %d\n", index);
   }
   else
   {
      puts("Value not found");
   }

   return 0;
}

size_t linearSearch(const int array[], const int key, const size_t size)
{
   // loop through array
   for (int n = 0; n < size; ++n)
   {
      if (array[n] == key)
      {
         return n; // return location of key
      }
   }

   return -1;
}
