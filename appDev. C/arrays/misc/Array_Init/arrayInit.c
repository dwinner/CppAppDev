// Example 5-4. Initializing an array
// arrayInit.c

#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 100

int main()
{
   double *pArray = NULL; 
   int i = 0;
   pArray = malloc( ARRAY_SIZE * sizeof(double) ); // Generate the array
   if ( pArray != NULL )
   {
      for ( i = 0; i < ARRAY_SIZE; ++i )           // and initialize it.
         pArray[i] = (double)rand()/RAND_MAX;
   /* ... */

      for( int i=0; i < ARRAY_SIZE; ++i)           // Print the array.
         printf("%8.4f", pArray[i]);

      free( pArray);
   }

   return 0;
}
