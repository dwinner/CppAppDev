// isfinite_ex.c : isfinite() example
// -------------------------------------------------------------

#include <math.h>     // int isfinite( float x );
                      // int isfinite( double x );
                      // int isfinite( long double x );

#include <stdarg.h>

double vsum( int n, ... )
// n is the number of arguments in the list
{
    va_list argptr;
    double sum = 0.0, next = 0.0;

    va_start( argptr, n );
    while ( n-- )
    {
        next = va_arg( argptr, double );
        sum += next;
        if ( isfinite( sum ) == 0 )
           break;         // If sum reaches infinity, stop adding.
    }
    va_end( argptr );
    return sum;
}

#include <stdio.h>
#include <float.h>

int main()
{
    printf( "1. Sum: %lf\n", vsum( 3, 1.0, 2.0, 3.0) );

    double x = DBL_MAX;
    printf( "2. Sum: %lf\n", vsum( 2, x, x) );
   
    return 0;
}

