// Example 7-7. Function swapf()
// selectionSort.c

// With gcc use the option -O  
// GCC does not inline any functions when not optimizing

// The function swapf() exchanges the values of two float variables.
// Arguments:    Two pointers to float.
// Return value: None.

inline void swapf( float *p1, float *p2 )      // An inline function.
{
   float tmp = *p1; *p1 = *p2; *p2 = tmp;
}

// The function selection_sortf() uses the selection-sort
// algorithm to sort an array of float elements.
// Arguments:    An array of float, and its length.
// Return value: None.

void selection_sortf( float a[], int n )   // Sort an array a of length n.
{
   register int i, j, mini;                // Three index variables.
   for ( i = 0; i < n - 1; ++i )
   {
      mini = i;             // Search for the minimum starting at index i.
      for ( j = i+1; j < n; ++j )
         if ( a[j] < a[mini] )
           mini = j;
      swapf( a+i, a+mini); // Swap the minimum with the element at index i.
   }
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
