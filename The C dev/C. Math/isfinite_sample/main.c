// isfinite_ex.c : isfinite() example
// -------------------------------------------------------------
// int isfinite( float x );
// int isfinite( double x );
// int isfinite( long double x );

#include <math.h>
#include <stdarg.h>

// n is the number of arguments in the list
double vsum(int n, ...)
{
   va_list argptr;
   double sum = 0.0, next = 0.0;

       va_start(argptr, n);
   while (n--)
   {
      next = va_arg(argptr, double);
      sum += next;

      // If sum reaches infinity, stop adding.
      if (isfinite(sum) == 0)
      {
         break;
      }
   }

       va_end(argptr);

   return sum;
}

#include <stdio.h>
#include <float.h>

int main()
{
   printf("1. Sum: %lf\n", vsum(3, 1.0, 2.0, 3.0));

   double x = DBL_MAX;
   printf("2. Sum: %lf\n", vsum(2, x, x));

   return 0;
}

