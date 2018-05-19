// Example 9-2. Pointer version of the selection_sortf() function
// selectionSort_ptr.c

// With gcc use the option -O  
// GCC does not inline any functions when not optimizing

// The swapf() function exchanges the values of two float variables.
// Arguments: Two pointers to float.

inline void swapf( float *p1, float *p2 )
{
   float tmp = *p1; *p1 = *p2; *p2 = tmp;      // Swap *p1 and *p2.
}

// The function selection_sortf() uses the selection-sort
// algorithm to sort an array of float elements.
// Arguments: An array of float, and its length.

void selection_sortf( float a[], int n )       // Sort an array a of
{                                              // n float elements.
   if ( n <= 1 ) return;               // Nothing to sort.

   register float *last = a + n-1,     // A pointer to the last element.
                  *p,                  // A pointer to a selected element.
                  *minPtr;             // A pointer to the current minimum.

   for ( ; a < last; ++a )             // Walk pointer a through the array.
   {
      minPtr = a;                      // Find the smallest element
      for ( p = a+1; p <= last; ++p )  // between a and the last element.
         if ( *p < *minPtr )
           minPtr = p;
      swapf( a, minPtr );              // Swap the smallest element
   }                                   // with the element at a.
}

#include <stdio.h>

int main()
{
   float fArr[] = { 2.2F , 0.0F, -1.1F, 3.3F, -4.4F };
   int n = sizeof(fArr)/sizeof(*fArr);

   selection_sortf( fArr, n);

   for ( int i = 0; i < n; ++i )
      printf("%8.2f", fArr[i]);
   putchar('\n');    
   return 0;
}
