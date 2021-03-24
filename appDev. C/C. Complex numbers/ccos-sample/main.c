// ccos_ex.c : ccos() example
// -------------------------------------------------------------

#include <complex.h>   // double complex ccos( double complex z );
// float complex ccosf( float complex z );
// long double complex ccosl( long double complex z );
#include <stdio.h>

/* Demonstrate the exponential definition
 * of the complex cosine function.
 */
int main()
{
   double complex z = 2.2 + 3.3 * I;
   double complex c, d;

   c = ccos(z);
   d = 0.5 * (cexp(z * I) + cexp(-z * I));

   printf("The ccos() function returns %.2f %+.2f × I.\n",
          creal(c),
          cimag(c));
   printf("Using the cexp() function, the result is %.2f %+.2f × I.\n",
          creal(d),
          cimag(d));

   return 0;
}
