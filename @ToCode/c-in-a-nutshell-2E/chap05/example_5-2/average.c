// Example 5-2. Operations with pointers
// average.c

/* The function average() calculates the arithmetic mean of the
 * numbers passed to it in an array.
 * Arguments: An array of float, and its length.
 * Return value: The arithmetic mean of the array elements, with type double.
 */
double average( const float *array, int length )
{
   double sum = 0.0;
   const float *end = array + length; // Points one past the last element.

   if ( length <= 0 )                 // The average of no elements is zero.
     return 0.0;
                                                // Accumulate the sum by 
   for ( const float *p = array; p < end; ++p)  // walking a pointer through 
     sum += *p;                                 // the array. 

   return sum/length;                 // The average of the element values.
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
   float arr[] = { 3.3F, 1.1F, 2.2F };
   int len = sizeof(arr)/sizeof(*arr);

   printf("Arithmetic mean: %.2f\n", average( arr, len));
   return 0;
}

