/**
 * Multipurpose sorting program using function pointers
 */

#include <stdio.h>
#include "bubble.h"

#define SIZE 10

int main()
{
   // initialize unordered array a
   int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};

   printf("%s", "Enter 1 to sort in ascending order,\n"
          "Enter 2 to sort in descending order: ");
   int order; // 1 for ascending order or 2 for descending order
   scanf_s("%d", &order);

   puts("\nData items in original order");

   // output original array
   for (size_t counter = 0; counter < SIZE; ++counter)
   {
      printf("%5d", a[counter]);
   }

   // sort array in ascending order; pass function ascending as an
   // argument to specify ascending sorting order
   if (order == 1)
   {
      bubble(a, SIZE, ascending);
      puts("\nData items in ascending order");
   }
   else
   {
      // pass function descending
      bubble(a, SIZE, descending);
      puts("\nData items in descending order");
   }

   // output sorted array
   for (size_t counter = 0; counter < SIZE; ++counter)
   {
      printf("%5d", a[counter]);
   }

   puts("\n");

   return 0;
}
