// Example 6-5. Nested loops in the bubble-sort algorithm
// Sort an array of float in ascending order
// using the bubble-sort algorithm.
// -----------------------------------------

void bubbleSort( float arr[], int len )   // The array arr and
{                                         // its length len.
   int isSorted = 0;
   do
   {
      float temp;             // Holder for values being swapped.
      isSorted = 1;
      --len;
      for ( int i = 0; i < len; ++i )
        if ( arr[i] > arr[i+1] )
        {
           isSorted = 0;      // Not finished yet.
           temp = arr[i];     // Swap adjacent values.
           arr[i] = arr[i+1];
           arr[i+1] = temp;
        }
   } while ( !isSorted );
}

#include <stdio.h>

int main()
{
  float fArr[] = { 2.2F , 0.0F, -1.1F, 3.3F, -4.4F };
  int n = sizeof(fArr)/sizeof(*fArr);

  bubbleSort( fArr, n);

  for ( int i = 0; i < n; ++i )
     printf("%8.2f", fArr[i]);
  putchar('\n');    
  return 0;
}
