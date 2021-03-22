// log_ex.c : log() example
// The following code prints some sample values for base 2,
// base e, and base 10 logarithms.
// -------------------------------------------------------------
// double log( double x )
// float logf( float x )
// long double logl( long double x )

#include <math.h>
#include <stdio.h>

int main()
{
   double x[] = {1E-100, 0.5, 2, exp(1), 10, 1E+100};

   puts("       x           log2(x)            log(x)          log10(x)\n"
        " ---------------------------------------------------------------");
   for (int i = 0; i < sizeof(x) / sizeof(x[0]); ++i)
   {
      printf("%#10.3G %+17.10G %+17.10G %+17.10G\n",
             x[i], log2(x[i]), log(x[i]), log10(x[i]));
   }

   return 0;
}
