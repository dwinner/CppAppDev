#include "insertion_sort.h"

#ifdef TRACE
#include <stdio.h>

static void print_pass(int array[], size_t length, unsigned int pass, size_t index);

#endif

void insertion_sort(int array[], const size_t length)
{
   // loop over length - 1 elements 
   for (size_t i = 1; i < length; i++)
   {
      size_t moveItemIndex = i; // initialize location to place element 
      const int insertedElement = array[i]; // holds element to insert

      // search for place to put current element 
      while (moveItemIndex > 0 && array[moveItemIndex - 1] > insertedElement)
      {
         // shift element right one slot 
         array[moveItemIndex] = array[moveItemIndex - 1];
         --moveItemIndex;
      }

      array[moveItemIndex] = insertedElement; // place inserted element 

#ifdef TRACE
      print_pass(array, length, i, moveItemIndex);
#endif
   }
}

#ifdef TRACE
/**
 * \brief Prints a pass of the algorithm 
 * \param array Array to trace
 * \param length Array length
 * \param pass Passed index
 * \param index Selected index
 */
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
   for (size_t i = 0; i <= pass; i++)
   {
      printf("%s", "--  ");
   }

   puts(""); // add newline 
}

#endif
