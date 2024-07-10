#include "parallel_sum.h"
#include <threads.h>

// Recursive helper function to divide the work among several threads.
static int parallel_sum(void* arg);

bool sum(const float arr[], const int len, double* sumPtr)
{
   int blockSize = len / MAX_THREADS;
   if (blockSize < MIN_BLOCK_SIZE)
   {
      blockSize = len;
   }

   SumArg args = {arr, len, blockSize, 0.0};
   if (parallel_sum(&args))
   {
      *sumPtr = args.sum;
      return true;
   }

   return false;
}

static int parallel_sum(void* arg)
{
   SumArg* argp = (SumArg*)arg; // A pointer to the arguments.
   if (argp->len <= argp->block_size) // If length <= block_size, add up the elements.
   {
      for (int i = 0; i < argp->len; ++i)
      {
         argp->sum += argp->start[i];
      }

      return 1;
   }

   // If length > block_size, divide the array.
   const int mid = argp->len / 2;

   // Specifies 2nd half length of first half
   SumArg arg2 =
   {
      argp->start + mid,
      argp->len - mid,
      argp->block_size,
      0
   };
   argp->len = mid;
   thrd_t th; // Process 1st half in a new thread.
   int res = 0;
   if (thrd_create(&th, parallel_sum, arg) != thrd_success)
   {
      return 0; // Couldn't spawn a thread
   }

   if (!parallel_sum(&arg2)) // Process 2nd half by recursion in the current thread.
   {
      thrd_detach(th);
      return 0; // Recursive call failed
   }

   thrd_join(th, &res);
   if (!res)
   {
      return 0; // Sibling thread reported failure
   }

   argp->sum += arg2.sum;

   return 1;
}
