// ctan_ex.c : ctan() example
// --------------------------------------------------------------------

#include <complex.h>  // double complex ctan( double complex z );
// float complex ctanf( float complex z );
// long double complex ctanl( long double complex z );
#include <stdio.h>

int main()
{
   double complex z = -0.53 + 0.62 * I;
   double complex c, d;

   c = ctan(z);
   d = csin(z) / ccos(z);

   printf("The ctan() function returns %.2f %+.2f * I.\n",
          creal(c),
          cimag(c));
   printf("Using the csin() and ccos() functions yields %.2f %+.2f * I.\n",
          creal(d),
          cimag(d));

   return 0;
}
