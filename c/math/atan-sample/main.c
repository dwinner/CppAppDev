// atan_ex.c : atan() example
// -------------------------------------------------------------

#include <math.h>    // double atan( double x );
// float atanf( float x );
// long double atanl( long double x );
#include <stdio.h>

int main()
{
#ifdef PI
   printf("The symbol PI was already defined.\n");
   long double pi = (long double) PI;
#else
   long double pi = 4.0L * atanl(1.0L);    // Because tan(pi/4) = 1
#endif
   printf("Assume pi equals %.17Lf.\n", pi);

   return 0;
}
