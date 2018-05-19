// Example 7-2. Function printArray()
// printArray.c

#include <stdio.h>

static void printArray( const float [], int );

int main()
{
    float farray[123];
    int len = sizeof(farray) / sizeof(*farray);

    for( int i = 0; i < len; ++i)
      farray[i] = (float)(100.0 / i);

    printArray( farray, 123 );
    return 0;
}

// The static function printArray() prints the elements of an array
// of float to standard output, using printf() to format them.
// Arguments: An array of float, and its length.
// Return value: None.

static void printArray( const float array[], int n )
{
   for ( int i=0; i < n; ++i )
   {
     printf( "%12.2f", array[i] );    // Field width: 12; decimal places: 2.
     if( i % 5 == 4 ) putchar('\n');  // New line after every 5 numbers.
   }
   if ( n % 5 != 0 ) putchar('\n');   // New line at the end of the output.
}
