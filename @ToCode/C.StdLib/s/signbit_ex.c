// signbit_ex.c : signbit() example
// -------------------------------------------------------------

#include <math.h>   // int signbit(x );
#include <stdio.h>

int main()
{
    double x[ ] = { -0.0, 187.234, sqrt( -1.0 ), 1.0 / -0.0 };

    for ( int i = 0 ; i < ( sizeof(x) / sizeof(double)) ; i++ )
        printf( "x[%d] equals %lF, and is%s negative.\n",
                 i, x[i], signbit( x[i] ) ? "" : " not" );    
    return 0;
}
