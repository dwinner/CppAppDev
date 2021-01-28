// fabs_ex.c : fabs() example
// -------------------------------------------------------------
// double fabs( double x );
// float fabsf( float x );
// long double fabsl( long double x );

#include <math.h>
#include <stdio.h>

int main()
{
   float x = 4.0F * atanf(1.0F);
   long double y = 4.0L * atanl(1.0L);

   if (x == y)
   {
      printf("x and y are exactly equal.\n");
   }
   else if (fabs(x - y) < 0.0001 * fabsl(y))
   {
      printf("x and y are approximately equal:\n"
             "x is %.8f; y is %.8Lf.\n", x, y);
   }

   return 0;
}
