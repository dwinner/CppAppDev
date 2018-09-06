// casinh_ex.c : casinh() example
// -------------------------------------------------------------

#include <complex.h>   // double complex casinh( double complex z );
                       // float complex casinhf( float complex z );
                       // long double complex casinhl( long double complex z );
#include <stdio.h>

int main()
{
    double complex v, w, z ;
    double a = 0.0, b = 0.0;

    puts("Enter the real and imaginary parts of a complex number:");
    if ( scanf("%lf %lf", &a, &b) == 2)
    {
        z = a + b * I;
        printf( "z = %.2f %+.2f*I.\n", creal(z), cimag(z) );

        v = casin(z);
        w = casinh(z);
        printf( "z is the sine of %.2f %+.2f*I\n", creal(v), cimag(v) );
        printf( "and the hyperbolic sine of %.2f %+.2f*I.\n",
                creal(w), cimag(w) );
    }
    else
        printf("Invalid input. \n");

    return 0;
}
