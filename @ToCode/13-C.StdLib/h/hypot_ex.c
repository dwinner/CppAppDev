// hypot_ex.c : hypot() example
// -------------------------------------------------------------

#include <math.h>   // double hypot( double x, double y );
                    // float hypotf( float x, float y );
                    // long double hypotl( long double x, long double y );
#include <stdio.h>
#include <errno.h>

int main()
{
    double x, y, h;        // Three sides of a triangle

    printf( "How many kilometers do you want to go westward? " );
    scanf( "%lf", &x );

    printf( "And how many southward? " );
    scanf( "%lf", &y );

    errno = 0;
    h = hypot( x, y );
    if ( errno )
       perror( __FILE__ );
    else
       printf( "Then you'll be %4.2lf km from where you started.\n", h );

    return 0;
}
