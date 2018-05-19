// Example 6-7. The break statement
// getScores.c : 
// Read user input of scores from 0 to 100
// and store them in an array.
// Return value: the number of values stored.
// --------------------------------------------

#include <stdio.h>

int getScores( short scores[ ], int len )
{
   int i = 0;
   puts( "Please enter scores between 0 and 100.\n"
         "Press <Q> and <Return> to quit.\n" );
   while ( i < len )
   {
      printf( "Score No. %2d: ", i+1 );
      if ( scanf( "%hd", &scores[i] ) != 1 )
         break;            // No number read: end the loop.
      if ( scores[i] < 0 || scores[i] > 100 )
      {
         printf( "%d: Value out of range.\n", scores[i] );
         break;            // Discard this value and end the loop.
      }
      ++i;
   }
   return i; // The number of values stored.
}

int main()
{
   short scores[10] = { 0 };
   int len = sizeof(scores)/sizeof(*scores);

   int n = getScores( scores, len);

   printf("The %d scores are:\n", n);
   for( int i = 0; i < n; ++i)
      printf("%6d", scores[i]);
   return 0;
}

