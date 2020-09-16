// fdim_ex.c : fdim() example
// -------------------------------------------------------------

#include <math.h>        // double fdim( double x, double y );
                         // float fdimf( float x, float y );
                         // long double fdiml( long double x, long double y );
#include <stdio.h>

int main()
{
    /* Make sure an argument is within the domain of asin() */

    double sign, argument = -1.5, result;
    /* ... */

    sign = copysign( 1.0, argument );           // Save the sign ...
    argument = copysign( argument, 1.0 );       // then use only positive values

    argument = 1.0 - fdim( 1.0, argument );     // Trim excess beyond 1.0
    result = asin( copysign(argument, sign) );  // Restore sign and
                                                // call asin()
    printf( "For the argument %.2lf the asin function returns %lf.\n",
             copysign(argument, sign), result );

    return 0;
}
