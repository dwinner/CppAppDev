// exp_ex.c : exp() example
// -------------------------------------------------------------
// double exp( double x );
// float expf( float x );
// long double expl( long double x );

#include <math.h>
#include <stdio.h>

int main()
{
   /* Amount owed = principal * e^(interest_rate * time) */

   int principal = 10000;   // Initial debt is ten thousand dollars.
   int balance = 0;
   double rate = 0.055;     // Interest rate is 5.5% annually.
   double time = 1.5;       // Period is eighteen months.

   balance = principal * exp(rate * time);

   printf("Invest %d dollars at %.1f%% compound interest, and "
          "in %.1f years \nyou'll have %d dollars.\n",
          principal, rate * 100.0, time, balance);

   return 0;
}
