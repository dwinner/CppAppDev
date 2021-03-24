// log2_ex.c : log2() example
// -------------------------------------------------------------
// double log2( double x )
// float log2f( float x )
// long double log2l( long double x )

#include <math.h>
#include <errno.h>
#include <stdio.h>

int main()
{
   double x[] = {0, 0.7, 1.8, 1234, INFINITY};

   for (int i = 0; i < sizeof(x) / sizeof(double); i++)
   {
      errno = 0;
      printf("The base 2 log of  %.1f is %.3f.\n", x[i], log2(x[i]));
      if (errno == EDOM || errno == ERANGE)
      {
         perror(__FILE__);
      }
   }

   return 0;
}
