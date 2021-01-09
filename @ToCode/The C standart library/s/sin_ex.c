// sin_ex.c : sin() example
// -------------------------------------------------------------

#include <math.h>    // double sin( double x );
                     // double sinf( float x );
                     // long double sinl( long double x );
#include <stdio.h>
#include <stdlib.h>

#define DEG_PER_RAD ( 180.0 / PI )

int main()
{
    const double PI = 4.0 * atan( 1.0 );
    double a[4];

    printf( "\nEnter an acute angle measure, in degrees: " );

    if ( scanf( "%lf", a ) < 1 || ( a[0] <= 0 || a[0] >= 90 ) )
        printf( "\nThat's not an acute angle.\n" ), exit( 1 );
    else
    {
        a[1] = a[0] + 90 ;
        a[2] = 180 - a[0] ;
        a[3] = 225 + a[0] ;

        for ( int i = 0 ; i < 4 ; i ++ )
            printf( "The sine of %6.2lf degrees is %6.4lf.\n",
                    a[i], sin( a[i] / DEG_PER_RAD ) );
    }
    return 0;
}
