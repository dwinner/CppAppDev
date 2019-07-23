// catan_ex.c : catan() example
// -------------------------------------------------------------

#include <complex.h>   // double complex catan( double complex z );
                       // float complex catanf( float complex z );
                       // long double complex catanl( long double complex z );
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

        v = catan(z);
        w = catanh(z);
        printf( "z is the tangent of %.2f %+.2f*I\n", creal(v), cimag(v) );
        printf( "and the hyperbolic tangent of %.2f %+.2f*I.\n",
                creal(w), cimag(w) );
    }
    else
        printf("Invalid input. \n");

    return 0;
}
