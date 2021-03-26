/**
 * Calculating the sum of array elements in several parallel threads
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parallel_sum.h"

#define ARRSIZE 1000000

float arr[ARRSIZE];

int main()
{
   double arrSum = 0;

   for (int i = 0; i < ARRSIZE; ++i)
   {
      arr[i] = (float)(i / 10.0);
   }

   const clock_t t1 = clock();
   if (!sum(arr, ARRSIZE, &arrSum))
   {
      fprintf(stderr, "Error in executing sum()\n");
      return EXIT_FAILURE;
   }

   const clock_t t2 = clock();
   printf("CPU time used: %ld milliseconds.\n",
          (t2 - t1) * 1000 / CLOCKS_PER_SEC);

   printf("The sum %.1f + %.1f + ... + %.1f = %.1lf\n",
          arr[0], arr[1], arr[ARRSIZE - 1], arrSum);
   printf("The correct sum is: %lld\n", (long long)ARRSIZE * (ARRSIZE - 1) / 20);

   printf("main() terminated.\n");

   return EXIT_SUCCESS;
}
