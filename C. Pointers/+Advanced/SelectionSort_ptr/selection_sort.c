#include "selection_sort.h"

/**
 * The swapf() function exchanges the values of two float variables.
 * @param p1 1st pointer to float
 * @param p2 2nd pointer to float
 */
static inline void swapf(float *p1, float *p2)
{
   float tmp = *p1;
   *p1 = *p2;
   *p2 = tmp;      // Swap *p1 and *p2.
}

/**
 * The function selection_sortf() uses the selection-sort
 * algorithm to sort an array of float elements.
 * @param a An array of float
 * @param n An array's length
 */
void selection_sortf(float a[], int n)       // Sort an array a of
{                                              // n float elements.
   if (n <= 1)
   {
      return;  // Nothing to sort.
   }

   register float *last = a + n - 1,     // A pointer to the last element.
   *p,                  // A pointer to a selected element.
   *minPtr;             // A pointer to the current minimum.

   for (; a < last; ++a)             // Walk pointer a through the array.
   {
      minPtr = a;                      // Find the smallest element
      for (p = a + 1; p <= last; ++p)  // between a and the last element.
      {
         if (*p < *minPtr)
         {
            minPtr = p;
         }
      }

      swapf(a, minPtr);              // Swap the smallest element
   }                                   // with the element at a.
}