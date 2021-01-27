// cacosh_ex.c : cacosh() example
// -------------------------------------------------------------

#include <complex.h>   // double complex cacosh( double complex z );
// float complex cacoshf( float complex z );
// long double complex cacoshl( long double complex z );
#include <stdio.h>

int main()
{
   double complex v, z;
   double a = 0.0, b = 0.0;

   puts("Calculate the inverse hyperbolic cosine of a complex number,"
        " cacosh(z)\n");
   puts("Enter the real and imaginary parts of a complex number:");
   if (scanf("%lf %lf", &a, &b) == 2)
   {
      z = a + b * I;
      printf("z = %.2f %+.2f*I.\n", creal(z), cimag(z));

      v = cacosh(z);
      printf("The cacosh(z) function yields %.2f %+.2f*I.\n",
             creal(v), cimag(v));
      printf("The inverse function, ccosh(cacosh(z)),"
             " yields %.2f %+.2f*I.\n",
             creal(ccosh(v)), cimag(ccosh(v)));
   }
   else
   {
      printf("Invalid input.\n");
   }

   return 0;
}
