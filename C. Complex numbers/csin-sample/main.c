// csin_ex.c : csin() example
// Demonstrate the exponential definition of the complex sine function.
// --------------------------------------------------------------------

#include <complex.h>  // double complex csin( double complex z );
// float complex csinf( float complex z );
// long double complex csinl( long double complex z );
#include <stdio.h>

int main()
{
   double complex z = 4.3 - 2.1 * I;
   double complex c, d;

   c = csin(z);
   d = (cexp(z * I) - cexp(-z * I)) / (2 * I);

   printf("The csin() function returns %.2f %+.2f * I.\n",
          creal(c),
          cimag(c));
   printf("Using the cexp() function, the result is %.2f %+.2f * I.\n",
          creal(d),
          cimag(d));

   return 0;
}
