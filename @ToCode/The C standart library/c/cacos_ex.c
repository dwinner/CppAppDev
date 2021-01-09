// cacos_ex.c : cacos() example
// -------------------------------------------------------------

#include <complex.h>   // double complex cacos( double complex z );
                       // float complex cacosf( float complex z );
                       // long double complex cacosl( long double complex z );
#include <stdio.h>

int main()
{
    double complex v, z;
    double a = 0.0, b = 0.0;

    puts("Calculate the arc cosine of a complex number, cacos(z)\n");
    puts("Enter the real and imaginary parts of a complex number:");
    if (scanf("%lf %lf", &a, &b) == 2)
    {
        z = a + b * I;
        printf("z = %.2f %+.2f*I.\n", creal(z), cimag(z));

        v = cacos(z);
        printf("The cacos(z) function yields %.2f %+.2f*I.\n",
                creal(v), cimag(v));
        printf("The inverse function, ccos(cacos(z)), yields %.2f %+.2f*I.\n",
                creal(ccos(v)), cimag(ccos(v)));
    }
    else
        printf("Invalid input. \n");

    return 0;
}
