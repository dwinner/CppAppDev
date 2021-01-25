// log1p_ex.c : log1p() example
// -------------------------------------------------------------

#include <math.h>    // double log1p( double x )
                     // float log1pf( float x )
                     // long double log1pl( long double x )
#include <stdio.h>

// atanh(x) is defined as 0.5 * ( log(x+1) - log(-x+1).
// Rounding errors can result in different results
// for different methods.

int main()
{
    puts("   x         atanh(x)    atanh(x) - 0.5*(log1p(x) - log1p(-x))\n"
         "--------------------------------------------------------------");
    for ( double x = -0.8; x < 1.0; x += 0.4)
    {
       double y = atanh(x);
       printf("%6.2f %14f %20E\n", x, y, y - 0.5*(log1p(x) - log1p(-x)) );
    }

    return 0;
}
