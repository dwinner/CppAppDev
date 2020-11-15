// csinh_ex.c : csinh() example
// --------------------------------------------------------------------

#include <complex.h>  // double complex csinh( double complex z );
                      // float complex csinhf( float complex z );
                      // long double complex csinhl( long double complex z );
#include <stdio.h>

int main()
{
    double complex v, w, z = -1.2 + 3.4 * I;

    v = csinh( z );
    w = 0.5 * ( cexp(z) - cexp(-z) );

    printf( "The csinh() function returns %.2f %+.2f*I.\n",
            creal(v), cimag(v) );
    printf( "Using the cexp() function, the result is %.2f %+.2f*I.\n",
            creal(w), cimag(w) );

    return 0;
}
