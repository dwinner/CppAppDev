/**
 * Nested loops in the bubble-sort algorithm
 * Sort an array of float in ascending order
 * using the bubble-sort algorithm.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Sort array
 * \param array Array to sort
 * \param len Length of array
 */
void bubble_sort(float array[], int len)
{
   bool isSorted = false;

   do
   {
      isSorted = true;
      --len;
      for (int i = 0; i < len; ++i)
      {
         if (array[i] > array[i + 1])
         {
            isSorted = false; // Not finished yet.
            const float temp = array[i]; // Swap adjacent values
            array[i] = array[i + 1];
            array[i + 1] = temp;
         }
      }
   }
   while (!isSorted);
}

int main()
{
   float fArr[] = {2.2F, 0.0F, -1.1F, 3.3F, -4.4F};
   const int n = sizeof fArr / sizeof *fArr;

   bubble_sort(fArr, n);

   for (int i = 0; i < n; ++i)
   {
      printf("%8.2f", fArr[i]);
   }

   putchar('\n');

   return EXIT_SUCCESS;
}
