/**
 * The selection sort algorithm
 */

#include <stdio.h>
#include <time.h>

#include "selection_sort.h"

#define SIZE 10

int main(void)
{
   int array[SIZE]; // declare the array of ints to be sorted 

   srand(time(NULL)); // seed the rand function 

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
   selection_sort(array, SIZE);
   puts("Sorted array:");

   for (size_t i = 0; i < SIZE; i++)
   {
      // print the array 
      printf("%d  ", array[i]);
   }
}
