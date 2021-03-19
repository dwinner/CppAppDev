// trunc_ex.c : trunc() example
// -------------------------------------------------------------

#include <math.h>    // double trunc( double x );
                     // float truncf( float x );
                     // long double truncl( long double x );
#include <stdio.h>

int main()
{
    printf("trunc(-1.7) = %.2f  trunc(1.4) = %.2f  trunc(1.5) = %.2f\n",
            trunc(-1.7), trunc(1.4), trunc(1.5) );

    printf("round(-1.7) = %.2f  round(1.4) = %.2f  round(1.5) = %.2f\n",
            round(-1.7), round(1.4), round(1.5) );

    return 0;
}
