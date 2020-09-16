// acos_ex.c : acos() example
// -------------------------------------------------------------

#include <math.h>    // double acos( double x );
                     // float acosf( float x ); 
                     // long double acosl( long double x );
#include <stdio.h>

/*
 * Calculate the pitch of a roof given
 * the sloping width from eaves to ridge and
 * the horizontal width of the floor below it.
*/

#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main()
{
    double floor_width = 30.0;
    double roof_width = 34.6;

    double roof_pitch = acos( floor_width / roof_width ) * DEG_PER_RAD ;
    printf( "The pitch of the roof is %2.0f degrees.\n", roof_pitch );

   return 0;
}
