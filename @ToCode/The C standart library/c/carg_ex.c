// carg_ex.c : carg() example
// -------------------------------------------------------------

#include <complex.h>   // double carg( double complex z );
                       // float cargf( float complex z );
                       // long double cargl( long double complex z );
#include <stdio.h>

int main()
{
    /* Convert a complex number from Cartesian to polar coordinates. */
    double complex z = -4.4 + 3.3 * I;
    double radius = cabs( z );
    double argument = carg( z );

    double x = creal( z );
    double y = cimag( z );

    printf( "Cartesian (x, y): (%4.1f, %4.1f)\n", x, y );
    printf( "Polar (r, theta): (%4.1f, %4.1f)\n", radius, argument );

    return 0;
}
