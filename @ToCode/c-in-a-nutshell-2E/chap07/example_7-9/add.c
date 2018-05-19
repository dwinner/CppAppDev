// Example 7-9. Function add()
// add.c

#include <stdarg.h>

// The add() function computes the sum of the optional arguments.
// Arguments: The mandatory first argument indicates the number of
//            optional arguments. The optional arguments are
//            of type double.
// Return value: The sum, with type double.

double add( int n, ... )
{
   int i = 0;
   double sum = 0.0;
   va_list argptr;
   va_start( argptr, n );              // Initialize argptr;

   for ( i = 0; i < n; ++i )           // that is, for each optional argument,
     sum += va_arg( argptr, double );  // read an argument with type double
                                       // and accumulate in sum.
   va_end( argptr );
   return sum;
}

#include <stdio.h>

int main()
{
   double n1 = 1.1, n2 = 2.2, n3 = 3.3, n4 = 4.4;

   printf("%.1f + %.1f + %.1f + %.1f = %.1f\n", 
           n1, n2, n3, n4, add( 4, n1, n2, n3, n4));
   return 0;
}
