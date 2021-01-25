// remquo_ex.c : remquo() example
// -------------------------------------------------------------

#include <math.h>   // double remquo( double x, double y, int *quo );
                    // float remquof( float x, float y, int *quo );
                    // long double remquol( long double x, long double y,
                    //                      int *quo );
#include <stdio.h>

int main()
{
    double apples = 0.0, people = 0.0, left = 0.0, share = 0.0;
    int quotient = 0;

    printf( "\nHow many people? ");
    scanf( "%lf", &people );

    printf( "\nHow many apples? ");
    scanf( "%lf", &apples );

    share = nearbyint( apples / people );
    left = remquo( apples, people, &quotient );    

    printf( "If there are %.2lf of us and %.2lf apples, "
            "each of us gets %.2lf apple%s, with %.2lf left over.\n",
            people, apples, share, ( share == 1 ) ? "" : "s", left );

    printf( "remquo() stored %d as the quotient "
            " of the division (modulo 8).\n", quotient );

    printf( "Test: share modulo 8 - quotient = %d\n",
            (int) share % 8 - quotient );

    return 0;
}
