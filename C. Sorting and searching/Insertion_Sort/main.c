/**
 * The insertion sort algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "insertion_sort.h"

#define SIZE 10

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

   for (size_t i = 0; i < SIZE; i++)
   {
      // print the array 
      printf("%d  ", array[i]);
   }

   puts("\n");
   insertion_sort(array, SIZE);
   puts("Sorted array:");

   for (size_t i = 0; i < SIZE; i++)
   {
      // print the array 
      printf("%d  ", array[i]);
   }

   return EXIT_SUCCESS;
}
