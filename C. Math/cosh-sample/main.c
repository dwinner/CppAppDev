// coshh_ex.c : cosh() example
// -------------------------------------------------------------

#include <math.h>   // double cosh( double x );
// float coshf( float x );
// long double coshl( long double x );
#include <stdio.h>

int main()
{
   double x, sum = 1.0;
   unsigned max_n;

   printf("Cosh(x) is the sum as n goes from 0 to infinity "
          "of x^(2*n) / (2*n)!\n");
   // That's x raised to the power of 2*n, divided by 2*n factorial.

   printf("Enter x and a maximum for n (separated by a space): ");
   if (scanf(" %lf %u", &x, &max_n) < 2)
   {
      printf("Couldn't read two numbers.\n");
      return -1;
   }

   printf("cosh(%.2f) = %.4f;\n", x, cosh(x));

   for (unsigned n = 1; n <= max_n; n++)
   {
      unsigned factor = 2 * n; // Calculate (2*n)!
      unsigned divisor = factor;

      while (factor > 1)
      {
         factor--;
         divisor *= factor;
      }

      sum += pow(x, 2 * n) / divisor; // Accumulate the series
   }

   printf("Approximation by series of %u terms = %.4f.\n", max_n + 1, sum);

   return 0;
}
