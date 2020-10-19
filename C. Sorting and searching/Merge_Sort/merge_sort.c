#include <stdio.h>
#include "merge_sort.h"

#ifdef TRACE

/**
 * \brief Display certain elements in array 
 * \param array Array to print
 * \param left Left index
 * \param right Right index
 */
static void display_sub_array(int array[], size_t left, size_t right);

#endif

/**
 * \brief Sorts a piece of the array 
 * \param array Array to sort
 * \param low The low index
 * \param high The high index
 */
static void sort_sub_array(int array[], size_t low, size_t high);

/**
 * \brief Merge two sorted subarrays into one sorted subarray 
 * \param array Array to merge
 * \param left Index of the left subarray
 * \param middle1 Index of the 1st middle
 * \param middle2 Index of the 1st middle
 * \param right Index of the right subarray
 */
static void merge(int array[], size_t left, size_t middle1, size_t middle2, size_t right);

#ifdef TRACE

static void display_sub_array(int array[], const size_t left, const size_t right)
{
   // output spaces for alignment
   for (size_t i = 0; i < left; i++)
   {
      printf("%s", "   ");
   }

   // output elements left in array 
   for (size_t i = left; i <= right; i++)
   {
      printf(" %d", array[i]);
   }
}

#endif

static void merge(int array[], const size_t left, const size_t middle1, const size_t middle2, const size_t right)
{
   size_t leftIndex = left; // index into left subarray
   size_t rightIndex = middle2; // index into right subarray
   size_t combinedIndex = left; // index into temporary array
   int tempArray[SIZE]; // temporary array

#ifdef TRACE

   // output two subarrays before merging
   printf("%s", "merge:   ");
   display_sub_array(array, left, middle1);
   printf("%s", "\n         ");
   display_sub_array(array, middle2, right);
   puts("");

#endif

   // merge the subarrays until the end of one is reached
   while (leftIndex <= middle1 && rightIndex <= right)
   {
      // place the smaller of the two current elements in result
      // and move to the next space in the subarray
      if (array[leftIndex] <= array[rightIndex])
      {
         tempArray[combinedIndex++] = array[leftIndex++];
      }
      else
      {
         tempArray[combinedIndex++] = array[rightIndex++];
      }
   }

   if (leftIndex == middle2) // if at the end of the left subarray...
   {
      while (rightIndex <= right) // copy the right subarray
      {
         tempArray[combinedIndex++] = array[rightIndex++];
      }
   }
   else // if at the end of the right subarray...
   {
      while (leftIndex <= middle1) // copy the left subarray
      {
         tempArray[combinedIndex++] = array[leftIndex++];
      }
   }

   // copy values back into the original array
   for (size_t i = left; i <= right; i++)
   {
      array[i] = tempArray[i];
   }

#ifdef TRACE
   // output merged subarray
   printf("%s", "         ");
   display_sub_array(array, left, right);
   puts("\n");
#endif
}

static void sort_sub_array(int array[], const size_t low, const size_t high)
{
   // test base case: size of array is 1
   if (high - low >= 1) // if not the base case...
   {
      const size_t middle1 = (low + high) / 2;
      const size_t middle2 = middle1 + 1;

#ifdef TRACE
      // output split step 
      printf("%s", "split:   ");
      display_sub_array(array, low, high);
      printf("%s", "\n         ");
      display_sub_array(array, low, middle1);
      printf("%s", "\n         ");
      display_sub_array(array, middle2, high);
      puts("\n");
#endif

      // split array in half and sort each half recursively
      sort_sub_array(array, low, middle1); // 1st half
      sort_sub_array(array, middle2, high); // 2nd half

      // merge the two sorted arrays
      merge(array, low, middle1, middle2, high);
   }
}

void merge_sort(int array[], const size_t length)
{
   sort_sub_array(array, 0, length - 1);
}

void display_elements(int array[], const size_t length)
{
   display_sub_array(array, 0, length - 1);
}
