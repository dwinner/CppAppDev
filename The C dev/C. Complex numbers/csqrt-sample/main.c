// csqrt_ex.c : csqrt() example
// --------------------------------------------------------------------

#include <complex.h>  // double complex csqrt( double complex z );
// float complex csqrtf( float complex z );
// long double complex csqrtl( long double complex z );
#include <stdio.h>

int main()
{
   double complex z = 1.35 - 2.46 * I;
   double complex c, d;

   c = csqrt(z);
   d = c * c;

   printf("If the square root of %.2f %+.2f * I equals %.2f %+.2f * I,\n",
          creal(z), cimag(z), creal(c), cimag(c));
   printf("then %.2f %+.2f * I squared should equal %.2f %+.2f * I.\n",
          creal(c), cimag(c), creal(d), cimag(d));

   return 0;
}
