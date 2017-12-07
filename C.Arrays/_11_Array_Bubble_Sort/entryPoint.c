/**
 * Sorting an array's values into ascending order
 */
#include <stdio.h>
#define SIZE 10

int main(int argc, char* argv[])
{
   int a[SIZE] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };

   puts("Data items in original order");

   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%4d", a[i]);
   }

   // Bubble sort
   // loop to control number of passes
   for (unsigned int pass = 1; pass < SIZE; ++pass)
   {
      // loop to control number of comparisons per pass
      for (size_t i = 0; i < SIZE - 1; ++i)
      {
         // compare adjacent elements and swap them if first
         // element is greater than second element
         if (a[i] > a[i + 1])
         {
            const int hold = a[i];
            a[i] = a[i + 1];
            a[i + 1] = hold;
         }
      }
   }

   puts("\nData items in ascending order");

   for (size_t i = 0; i < SIZE; i++)
   {
      printf("%4d", a[i]);
   }

   puts("");

   return 0;
}
