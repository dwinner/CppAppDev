// fpclassify_ex.c : fpclassify() example
// -------------------------------------------------------------

#include <math.h>       // int fpclassify( x );
#include <stdio.h>

double minimum( double a, double b )
{
    register int aclass = fpclassify( a );
    register int bclass = fpclassify( b );

    if ( aclass == FP_NAN || bclass == FP_NAN )
       return NAN; 

    if ( aclass == FP_INFINITE )         // -Inf is less than anything;
       return ( signbit( a ) ? a : b );  // +inf is greater than anything.

    if ( bclass == FP_INFINITE )
       return ( signbit( b ) ? b : a );

    return ( a < b ? a : b );
}

int main()
{
    double x = 0.0;

    double min = minimum( x, -HUGE_VAL); 

    printf( "min = %G\n", min);
    return 0;
}
