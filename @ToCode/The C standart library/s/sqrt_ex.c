// sqrt_ex.c : sqrt() example
// -------------------------------------------------------------

#include <math.h>    // double sqrt( double x );
                     // double sqrtf( float x );
                     // long double sqrtl( long double x );
#include <stdio.h>
#include <errno.h>

int main()
{
    double x[ ] = { 0.5, 0.0, -0.0, -0.5 };

    for ( int i = 0; i < ( sizeof(x) / sizeof(double) ); i++)
    {
       printf("The square root of %.2F equals %.4F\n", x[i], sqrt( x[i] ) );
       if ( errno )
          perror( __FILE__ );
    }
    return 0;
}
