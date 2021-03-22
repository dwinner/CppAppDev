/**
 * The merge sort algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_sort.h"

int main()
{
   int array[SIZE]; // declare the array of ints to be sorted

   struct timespec ts;
   if (timespec_get(&ts, TIME_UTC) == 0)
   {
      printf("Error seeding random");
      return EXIT_FAILURE;
   }

   srand(ts.tv_nsec ^ ts.tv_sec); // seed the rand function 

   for (size_t i = 0; i < SIZE; i++)
   {
      array[i] = rand() % 90 + 10; // give each element a value 
   }

   puts("Unsorted array:");
   display_elements(array, SIZE); // print the array 
   puts("\n");
   merge_sort(array, SIZE); // merge sort the array 
   puts("Sorted array:");
   display_elements(array, SIZE); // print the array 

   return EXIT_SUCCESS;
}
