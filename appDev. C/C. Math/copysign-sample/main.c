// copysign_ex.c : copysign() example
// -------------------------------------------------------------

#include <math.h>
// double copysign( double x, double y );
// float copysignf( float x, float y );
// long double copysignl( long double x, long double y );
#include <stdio.h>

int main()
{
   /* Test for signed zero values */

   double x = copysign(0.0, -1.0);
   double y = copysign(0.0, +1.0);

   printf("x is %+.1f; y is %+.1f.\n", x, y);
   printf("%+.1f is %sequal to %+.1f.\n",
          x, (x == y) ? "" : "not ", y);
   return 0;
}
