// cpow_ex.c : cpow() example
// -------------------------------------------------------------

#include <complex.h>
// double complex cpow( double complex x, double complex y );
// float complex cpowf( float complex x, float complex y );
// long double complex cpowl( long double complex x, long double complex y );

#include <stdio.h>

int main()
{
    double complex z = 0.0 + 2.7 * I;
    double complex w = 2.7 + 0.0 * I;

    double complex c = cpow(w, z);   // Raise e to the power of i*2.7

    printf("%.2f %+.2f × I raised to the power of %.2f %+.2f × I \n"
           "is %.2f %+.2f × I.\n",
           creal(w), cimag(w), creal(z), cimag(z), creal(c), cimag(c));

    return 0;
}
