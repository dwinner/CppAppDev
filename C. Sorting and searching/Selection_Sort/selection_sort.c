#include "selection_sort.h"

#ifdef DEBUG
#include "stdio.h"
#endif

/**
 * \brief Swaps the array's elements
 * \param array Source array
 * \param first 1st First element to swap
 * \param second 2nd element to swap
 */
static void swap(int array[], size_t first, size_t second);

#ifdef DEBUG
/**
* \brief Traces the array sorting
* \param array Array to print
* \param length Array length
* \param pass Pass attempt
* \param index Selected index
*/
static void print_pass(int array[], size_t length, unsigned int pass, size_t index);
#endif

void selection_sort(int array[], const size_t arrayLength)
{
   // loop over length - 1 elements
   for (size_t i = 0; i < arrayLength - 1; ++i)
   {
      size_t smallest = i; // 1st index of remaining array

      // loop to find index of the smallest element
      for (size_t j = i + 1; j < arrayLength; j++)
      {
         if (array[j] < array[smallest])
         {
            smallest = j;
         }
      }

      swap(array, i, smallest); // swap the smallest element

#ifdef DEBUG
      print_pass(array, arrayLength, i + 1, smallest);
#endif
   }
}

static void swap(int array[], const size_t first, const size_t second)
{
   const int temp = array[first];
   array[first] = array[second];
   array[second] = temp;
}

#ifdef DEBUG
static void print_pass(int array[], const size_t length, const unsigned int pass, const size_t index)
{
   printf("After pass %2d: ", pass);

   // output elements till selected item 
   for (size_t i = 0; i < index; i++)
   {
      printf("%d  ", array[i]);
   }

   printf("%d* ", array[index]); // indicate swap 

   // finish outputting array 
   for (size_t i = index + 1; i < length; i++)
   {
      printf("%d  ", array[i]);
   }

   printf("%s", "\n               "); // for alignment 

   // indicate amount of array that is sorted 
   for (unsigned int i = 0; i < pass; i++)
   {
      printf("%s", "--  ");
   }

   puts(""); // add newline 
}
#endif
