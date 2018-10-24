// casin_ex.c : casin() example
// -------------------------------------------------------------

#include <complex.h>   // double complex casin( double complex z );
                       // float complex casinf( float complex z );
                       // long double complex casinl( long double complex z );
#include <stdio.h>

int main()
{
    puts("Results of the casin() function for integer values:");
    float complex z = 0;

    for ( int n = -3; n <= 3; ++n)
    {
        z = casinf(n);
        printf(" casin(%+d) = %+.2f %+.2f*I\n", n, crealf(z), cimagf(z) );
    }
    return 0;
}
