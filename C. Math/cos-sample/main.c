// cos_ex.c : cos() example
// -------------------------------------------------------------

#include <math.h>
// double cos( double x );
// float cosf( float x );
// long double cosl( long double x );
#include <stdio.h>

/*
 * Calculate the sloping width of a roof
 * given the horizontal width
 * and the angle from the horizontal.
 */
#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main()
{
   double roof_pitch = 20.0;        // In degrees
   double floor_width = 30.0;       // In feet, say.

   double roof_width = 1.0 / cos(roof_pitch / DEG_PER_RAD) * floor_width;

   printf("The sloping width of the roof is %4.2f ft.\n", roof_width);

   return 0;
}
