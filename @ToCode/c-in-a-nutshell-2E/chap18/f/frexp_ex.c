// frexp_ex.c : frexp() example
// -------------------------------------------------------------

#include <math.h>    // double frexp( double x, int *exp );
                     // float frexpf( float x, int *exp );
                     // long double frexpl( long double x, int *exp );
#include <stdio.h>
#include <stdlib.h>

double fourthrt( double x )
{
    int exponent, exp_mod_4;
    double mantissa = frexp( x, &exponent );

    exp_mod_4 = exponent % 4;
    exponent -= ( exp_mod_4 );    // Get an exponent that's
                                  // divisible by four ...
    for ( int i = abs( exp_mod_4 ); i > 0; i-- )
    {
        if ( exp_mod_4 > 0 )      // ... and compensate in the mantissa.
           mantissa *= 2.0;
       else
           mantissa /= 2.0;
    }
    return ldexp( sqrt( sqrt( mantissa )), exponent / 4 );
}

int main()
{
    double x = 64.0;      // 16 * 4

    printf( "The fourth root of %f is %G.\n", x, fourthrt(x) );
    return 0;
}
