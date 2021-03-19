// ilogb_ex.c : ilogb() example
// -------------------------------------------------------------

#include <math.h>    // int ilogb( double x )
                     // int ilogbf( float x )
                     // int ilogbl( long double x )
#include <stdio.h>
#include <limits.h>

int main()
{
    int exponent = 0;
    double x = -1.509812734e200;

    while ( exponent < INT_MAX )
    {
       exponent = ilogb( x );
       printf( "The exponent of %g is %d.\n", x, exponent );

       if ( x < 0.0 && x * x > 1.0 )
          x /= 1e34;
       else
          x += 1.1, x *= 2.2e34 ;
    }
    return 0;
}
