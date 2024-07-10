// ccosh_ex.c : ccosh() example
// -------------------------------------------------------------

#include <complex.h>   // double complex ccosh( double complex z );
// float complex ccoshf( float complex z );
// long double complex ccoshl( long double complex z );
#include <stdio.h>

int main()
{
   double complex v, w, z = 1.2 - 3.4 * I;
   v = ccosh(z);
   w = 0.5 * (cexp(z) + cexp(-z));

   printf("The ccosh() function returns %.2f %+.2f*I.\n",
          creal(v),
          cimag(v));
   printf("Using the cexp() function, the result is %.2f %+.2f*I.\n",
          creal(w),
          cimag(w));

   return 0;
}
