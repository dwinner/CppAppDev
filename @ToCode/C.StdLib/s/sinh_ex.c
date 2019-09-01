// sinh_ex.c : sinh() example
// -------------------------------------------------------------

#include <math.h>    // double sinh( double x );
                     // double sinhf( float x );
                     // long double sinhl( long double x );
#include <stdio.h>

// A chain hanging from two points forms a curve called a catenary.
// A catenary is a segment of the graph of the function
// cosh(k*x)/k, for some constant k.
// The length along the catenary over a certain span, bounded by the
// two vertical lines at x=a and x=b, is equal to
// sinh(k*b)/k - sinh(k*a)/k.

int main()
{
    double x, k;

    puts("Catenary f(x) = cosh(k*x)/k\n"
         "Length along the catenary from a to b: "
         "sinh(k*b)/k - sinh(k*a)/k)\n");

    puts("            f(-1.0)  f(0.0)   f(1.0)   f(2.0)   Length(-1.0 to 2.0)\n"
         "-------------------------------------------------------------------");
    for ( k = 0.5; k < 5; k *= 2)
    {
        printf("k = %.1f: ", k);
        for ( x = -1.0; x < 2.1; x += 1.0)
           printf("%8.2f ", cosh(k*x)/k );

        printf(" %12.2f\n", (sinh(2*k) - sinh(-1*k))/ k);
    }

    return 0;
}
