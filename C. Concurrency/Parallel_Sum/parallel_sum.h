#ifndef parallel_sum_h__
#define parallel_sum_h__

#include <stdbool.h>

/**
 * \brief Maximum number of threads to create
 */
#define MAX_THREADS  8

/**
 * \brief Minimum size of an array block
 */
#define MIN_BLOCK_SIZE 100

/**
 * \brief Arguments for the parallel_sum() function.
 */
typedef struct
{
   /**
    * \brief Start of the array block
    */
   const float* start; // Start and 

   /**
    * \brief Length of the array block
    */
   int len;

   /**
    * \brief Size of the smallest blocks
    */
   int block_size;

   /**
    * \brief The result
    */
   double sum;
} SumArg;

/**
 * \brief Sum of array elements
 * \param arr Array to sum
 * \param len Array length
 * \param sumPtr Argument for storing result
 * \return true, if calculation is successful, false - otherwise
 */
bool sum(const float arr[], const int len, double* sumPtr);

#endif // parallel_sum_h__
