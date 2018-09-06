// asin_ex.c : asin() example
// -------------------------------------------------------------

#include <math.h>    // double asin( double x );
                     // float asinf( float x ); 
                     // long double asinl( long double x );
#include <stdio.h>

/*
 * Calculate the altitude of the sun (its angle upward from the horizon)
 * given the height of a vertical object and the length of the object's
 * shadow.
*/

#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main()
{
    float height = 2.20F;
    float length = 1.23F;

    float altitude = asinf( height / sqrtf( height*height + length*length));

    printf( "The sun's altitude is %2.0f\xB0.\n", altitude * DEG_PER_RAD);    
    return 0;
}
