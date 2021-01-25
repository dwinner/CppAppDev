// logb_ex.c : logb() example
// -------------------------------------------------------------

#include <math.h>    // double logb( double x )
                     // float logbf( float x )
                     // long double logbl( long double x )
#include <errno.h>
#include <stdio.h>

int main()
{
    double x[] = { 0, 0, 0.7, 1.8, 1234, INFINITY };

    x[1] = nextafter( 0.0, 1.0 );

    for ( int i = 0; i < sizeof( x ) / sizeof( double ); i++ )
    {
        errno = 0;
        printf( "The exponent in the binary representation of %g is %g.\n",
                x[i], logb( x[i] ) );
        if ( errno == EDOM || errno == ERANGE )
           perror( __FILE__ );
    }

    return 0;
}
