// tanh_ex.c : tanh() example
// -------------------------------------------------------------

#include <math.h>    // double tanh( double x );
                     // float tanhf( float x );
                     // long double tanhl( long double x );
#include <stdio.h>

int main()
{
    double x = -0.5, y1, y2;

    y1 = tanh(x);
    y2 = exp(2*x);
    y2 = (y2 -1) / (y2 + 1);

    printf("The tanh() function returns     %.15f.\n", y1 );
    printf("Using the function exp() yields %.15f.\n", y2 );

    return 0;
}
