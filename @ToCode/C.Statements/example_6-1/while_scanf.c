// Example 6-1. A while loop
// while_scanf.c
// Read in numbers from the keyboard and
// print out their average.
// ----------------------------------------
#include <stdio.h>

int main()
{
   double x = 0.0, sum = 0.0;
   int count = 0;

   printf( "\t--- Calculate Averages ---\n" );
   printf( "\nEnter some numbers:\n"
           "(Type a letter to end your input)\n" );
   while ( scanf( "%lf", &x ) == 1 )
   {
      sum += x;
      ++count;
   }
   if ( count == 0 )
      printf( "No input data!\n" );
   else
      printf( "The average of your numbers is %.2f\n", sum/count );

   return 0;
}
