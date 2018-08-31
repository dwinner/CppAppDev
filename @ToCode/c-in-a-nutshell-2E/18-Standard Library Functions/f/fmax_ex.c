// fmax_ex.c : fmax() example
// -------------------------------------------------------------

#include <math.h>   // double fmax( double x, double y );
                    // float fmaxf( float x, float y );
                    // long double fmaxl( long double x , long double y );
#include <float.h>
#include <stdio.h>

int main()
{
    // Let big equal the second-greatest-possible double value ...
    const double big = nextafter( DBL_MAX, 0.0 );
    // ... and small the second-least possible-double value:
    const double small = nextafter( DBL_MIN, 0.0 );

    double a, b, c;
    /* ... */
    a = DBL_MIN;  b = 0.0;  c = 1.0;

    if ( fmin( fmin( a, b ), c ) <= small )
       printf( "At least one value is too small.\n" );
    if ( fmax( fmax( a, b ), c ) >= big )
       printf( "At least one value is too great.\n" );

    return 0;
}
