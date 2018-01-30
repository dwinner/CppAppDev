/**
 * Putting values into an array, sorting the values into
 * ascending order, and printing the resulting array.
 */
#include <stdio.h>
#define SIZE 10

void bubbleSort(int* array, size_t size);

int main()
{
   // initialize array a
   int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};

   puts("Data items in original order");

   // loop through array a
   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%4d", a[i]);
   }

   bubbleSort(a, SIZE); // sort the array

   puts("\nData items in ascending order");

   // loop through array a
   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%4d", a[i]);
   }

   puts("");

   return 0;
}

/**
 * @brief Sort array via bubble sorting alg
 *    @param array array to sort
 *    @param size array size
 */
void bubbleSort(int*const array, const size_t size)
{
   // local prototype declaration
   void swap(int* element1Ptr, int* element2Ptr);

   // loop to control passes
   for (unsigned int pass = 0; pass < size - 1; ++pass)
   {
      // loop to control comparisons during each pass
      for (size_t j = 0; j < size - 1; ++j)
      {
         // swap adjacent elements if they're out of order
         if (array[j] > array[j + 1])
         {
            swap(&array[j], &array[j + 1]);
         }
      }
   }
}

/**
 * @brief Swap values at memory to which element1Ptr and element2Ptr point
 *    @param element1Ptr 
 *    @param element2Ptr 
 */
void swap(int* element1Ptr, int* element2Ptr)
{
   const int hold = *element1Ptr;
   *element1Ptr = *element2Ptr;
   *element2Ptr = hold;
}
