// Example 7-8. Function binarySearch()
// binarySearch.c

#include <stdio.h>

// The binarySearch() function searches a sorted array.
// Arguments:    The value of the element to find;
//               the array of long to search; the array length.
// Return value: A pointer to the element found,
//               or NULL if the element is not present in the array.

long *binarySearch( long val, long array[ ], int n )
{
   int m = n/2;
   if ( n <= 0 )          return NULL;
   if ( val == array[m] ) return array + m;
   if ( val < array[m] )  return binarySearch( val, array, m );
   else                   return binarySearch( val, array+m+1, n-m-1 );
}

int main()
{
  long lArr[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
  int len = sizeof(lArr)/sizeof(*lArr);

  for ( int i = 0; i < len; ++i )
     printf("%6ld", lArr[i]);
  putchar('\n');

  long value = 0;
  printf( "\nEnter a whole number: ");
  scanf( "%ld", &value );

  long *ptr = binarySearch( value, lArr, len);

  if( ptr == NULL)
    printf("%ld is not an element of the array.\n", value);
  else
  { 
    int n = ptr+1 - lArr;
    printf("%ld is the %dth element in the arry.\n", value, n );
  }
  return 0;
}
