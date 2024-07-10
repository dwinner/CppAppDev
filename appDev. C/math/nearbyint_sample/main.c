// nearbyint_ex.c : nearbyint() example
// -------------------------------------------------------------

#include <math.h>    // double nearbyint( double x );
// float nearbyintf( float x );
// long double nearbyintl( long double x );
#include <fenv.h>
#include <stdio.h>

int main()
{
   if (fesetround(FE_TOWARDZERO) == 0)
   {
      printf("The current rounding mode is \"round toward 0.\"\n");
   }
   else
   {
      printf("The rounding mode is unchanged.\n");
   }

   printf("nearbyint(1.9) = %4.1f    nearbyint(-1.9) = %4.1f\n",
          nearbyint(1.9), nearbyint(-1.9));

   printf("round(1.9) = %4.1f        round(-1.9) = %4.1f\n",
          round(1.9), round(-1.9));

   return 0;
}
