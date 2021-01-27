// ctanh_ex.c : ctanh() example
// --------------------------------------------------------------------

#include <complex.h>  // double complex ctanh( double complex z );
// float complex ctanhf( float complex z );
// long double complex ctanhl( long double complex z );
#include <stdio.h>

int main()
{
   double complex v, w, z = -0.5 + 1.23 * I;

   v = ctanh(z);
   w = csinh(z) / ccosh(z);

   printf("The ctanh() function returns %.2f %+.2f*I.\n",
          creal(v), cimag(v));
   printf("Using the csinh() and ccosh() functions yields %.2f %+.2f*I.\n",
          creal(w), cimag(w));

   return 0;
}
