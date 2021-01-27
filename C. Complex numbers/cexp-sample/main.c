// cexp_ex.c : cexp() example
// -------------------------------------------------------------

#include <complex.h>   // double complex cexp( double complex z );
// float complex cexpf( float complex z );
// long double complex cexpl( long double complex z );
#include <stdio.h>

// Demonstrate Euler's theorem in the form
// e^(I*z) = cos(z) + I * sin(z)

int main()
{
   double complex z = 2.2 + 3.3 * I;
   double complex c, d;

   c = cexp(z * I);
   d = ccos(z) + csin(z) * I;

   printf("cexp( z*I ) yields %.2f %+.2f X I.\n",
          creal(c),
          cimag(c));
   printf("ccos( z ) + csin( z ) * I yields %.2f %+.2f X I.\n",
          creal(d),
          cimag(d));

   return 0;
}
