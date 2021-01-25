// Example 2-3. 
// usingvoid.c: Demonstrates uses of the type void
// -------------------------------------------------------
#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // Provides the following function prototypes:
// void srand( unsigned int seed );
// int rand( void );
// void *malloc( size_t size );
// void free( void *ptr );
// void exit( int status );

enum
{
   ARR_LEN = 100
};

int main()
{
   int i,                              // Obtain some storage space.
      *pNumbers = malloc(ARR_LEN * sizeof(int));

   if (pNumbers == NULL)
   {
      fprintf(stderr, "Insufficient memory.\n");
      exit(EXIT_FAILURE);
   }

   srand((unsigned) time(NULL));      // Initialize the
   // random number generator.

   for (i = 0; i < ARR_LEN; ++i)
   {
      pNumbers[i] = rand() % 10000;    // Store some random numbers.
   }

   printf("\n%d random numbers between 0 and 9999:\n", ARR_LEN);
   for (i = 0; i < ARR_LEN; ++i)       // Output loop:
   {
      printf("%6d", pNumbers[i]);       // Print one number per loop
      if (i % 10 == 9)  // every 10 numbers.
      {
         putchar('\n'); // iteration and a newline after
      }
   }

   free(pNumbers);                   // Release the storage space.
   return 0;
}
