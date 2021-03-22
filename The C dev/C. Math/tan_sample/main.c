// tan_ex.c : tan() example
// -------------------------------------------------------------

#include <math.h>    // double tan( double x );
// float tanf( float x );
// long double tanl( long double x );
#include <stdio.h>

int main()
{
   const double pi = 4.0L * atan(1.0);     // Because tan(pi/4) = 1
   double shadow_length = 85.5,
       angle = 36.2;         // Sun's elevation from the horizon, in
   // degrees
   double height = shadow_length * tan(angle * pi / 180);

   printf("The tower is %.2f meters high.\n", height);

   return 0;
}
