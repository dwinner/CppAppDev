// fma_ex.c : fma() example
// -------------------------------------------------------------
// double fma( double x, double y, double z );
// float fmaf( float x, float y, float z );
// long double fmal( long double x,
// long double y, long double z );

#include <math.h>
#include <stdio.h>

int main()
{
   double x, y, z;

   // Smallest possible double value
   x = nextafter(3.0, 4.0);

   // greater than 3
   y = 1.0 / 3.0;
   z = -1.0;

   printf("x = %.15G\n" "y = %.15G\n" "z = %.15G\n",
          x,
          y,
          z);

// #ifdef FP_FAST_FMA

   printf("fma( x, y, z) = %.15G\n", fma(x, y, z));

// #else // i.e., not def FP_FAST_FMA

   double product = x * y;
   printf("x times y = %.15G\n", product);
   printf("%.15G + z = %.15G\n", product, product + z);

// #endif // def FP_FAST_FMA
   return 0;
}
