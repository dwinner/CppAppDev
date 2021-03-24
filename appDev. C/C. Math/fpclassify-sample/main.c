// fpclassify_ex.c : fpclassify() example
// -------------------------------------------------------------
// int fpclassify( x );

#include <math.h>
#include <stdio.h>

double minimum(double a, double b)
{
   register int aclass = fpclassify(a);
   register int bclass = fpclassify(b);

   if (aclass == FP_NAN || bclass == FP_NAN)
   {
      return NAN;
   }

   // -Inf is less than anything;
   if (aclass == FP_INFINITE)
   {
      return (signbit(a) ? a : b);
   }

   // +inf is greater than anything.
   if (bclass == FP_INFINITE)
   {
      return (signbit(b) ? b : a);
   }

   return (a < b ? a : b);
}

int main()
{
   double x = 0.0;
   double min = minimum(x, -HUGE_VAL);
   printf("min = %G\n", min);

   return 0;
}
