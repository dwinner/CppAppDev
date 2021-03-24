// atan2_ex.c : atan2() example
// -------------------------------------------------------------

#include <math.h>    // double atan2( double x );
// float atan2f( float x );
// long double atan2l( long double x );
#include <stdio.h>

/*
 * Calculate an acute angle of a right triangle, given
 * the adjacent and opposite sides.
 */
#define PI 3.141593
#define DEG_PER_RAD (180.0/PI)

int main()
{
   double adjacent = 3.0;
   double opposite = 4.0;
   double angle = atan2(opposite, adjacent) * DEG_PER_RAD;

   printf("The acute angles of a 3-4-5 right triangle are %4.2f\xB0 "
          "and %4.2f\xB0.\n", angle, 90.0 - angle);

   return 0;
}
