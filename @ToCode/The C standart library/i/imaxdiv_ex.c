// imaxdiv_ex.c : imaxdiv() example
// -------------------------------------------------------------

#include <inttypes.h>  // imaxdiv_t imaxdiv( intmax_t dividend, 
                       //                    intmax_t divisor );
#include <stdio.h>

int main()
{
    intmax_t people = 110284, apples = 9043291;
    imaxdiv_t share;

    if ( people == 0 )       // Avoid dividing by zero.
    {
       printf( "There's no one here to take the apples.\n" ); 
       return -1;
    }
    else
       share = imaxdiv( apples, people );

    printf( "If there are %ji of us and %ji apples,\n"
            "each of us gets %ji, with %ji left over.\n",
            people, apples, share.quot, share.rem );

    return 0;
}
