// Example 14-1. Calculating the sum of array elements in several parallel threads
// parallelSum.c
// ----------------------------------------------------------------------------
#include <stdbool.h>
#include <threads.h>

#define MAX_THREADS 8             // 1, 2, 4, 8 ... Maximum number
                                  // of threads to create.
#define MIN_BLOCK_SIZE 100        // Minimum size of an array block.

typedef struct                    // Arguments for the parallel_sum() function.
{
    float *start;                 // Start and length of the
    int len;                      // array block passed to parallel_sum().
    int block_size;               // Size of the smallest blocks.
    double sum;                   // The result.
} Sum_arg;

int parallel_sum(void *arg);      // Prototype of the thread function.

// ---------------------------------------------------------------
// Calculate the sum of array elements and write it to *sumPtr.
// sum() calls the function parallel_sum() for parallel processing.
// Return value: true if no error occurs, otherwise false.

bool sum(float arr[], int len, double* sumPtr)
{
    int block_size = len / MAX_THREADS;
    if (block_size < MIN_BLOCK_SIZE) block_size = len;

    Sum_arg args = { arr, len, block_size, 0.0 };
    if (parallel_sum(&args))
    { 
        *sumPtr = args.sum; 
        return true;
    }
    else
        return false;
}

// ---------------------------------------------------------------
// Recursive helper function to divide the work among several threads.

int parallel_sum(void *arg)
{
    Sum_arg *argp = (Sum_arg*)arg;       // A pointer to the arguments.
    if (argp->len <= argp->block_size)   // If length <= block_size,
    {                                    // add up the elements.
        for (int i = 0; i < argp->len; ++i)
        argp->sum += argp->start[i];
        return 1;
    }
    else                                  // If length > block_size,
    {                                     // divide the array.
        int mid = argp->len / 2;
        Sum_arg arg2 = { argp->start+mid, argp->len-mid,
                         argp->block_size, 0};   // Specifies 2nd half
        argp->len = mid;                         // Length of first half

        thrd_t th;                     // Process 1st half in a new thread.
        int res = 0;

        if (thrd_create(&th, parallel_sum, arg) != thrd_success)
            return 0;                  // Couldn't spawn a thread

        if (!parallel_sum(&arg2))      // Process 2nd half by recursion
                                       // in the current thread.
        {
            thrd_detach(th); return 0; // Recursive call failed
        }
        thrd_join(th, &res);
        if (!res)
            return 0;                  // Sibling thread reported failure

        argp->sum += arg2.sum;
        return 1;
    }
}
