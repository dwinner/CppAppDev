// exp2_ex.c : exp2() example
// -------------------------------------------------------------
// double exp2( double x );
// float exp2f( float x );
// long double exp2l( long double x );

#include <math.h>
#include <stdio.h>

// The famous grains-of-rice-on-a-chessboard problem.
// The sultan loses a chess game. The wager was one grain for square 1
// on the chessboard, then double the last number for each successive
// square. How much rice in all?

int main()
{
   int squares = 64;
   long double gramspergrain = 0.0025L;   // A grain of rice weighs 25 mg.
   long double sum = 0.0L;

   for (int i = 0; i < squares; i++)
   {
      sum += gramspergrain * exp2l((long double) i);
   }

   printf("The sultan's wager costs him %.3Lf metric tons of rice.\n",
          sum / 1000000.0L);           // A million grams per ton.

   return 0;
}
