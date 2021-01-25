// div_ex.c : div() example
// -------------------------------------------------------------

#include <stdlib.h>   // div_t div(int dividend, int divisor );
                      // ldiv_t ldiv( long dividend, long divisor );
                      // lldiv_t lldiv( long long dividend, 
                      //                long long divisor );
#include <stdio.h>

int main()
{
    int people, apples;
    div_t share;

    for ( apples = -3 ; apples < 6 ; apples += 3 )
    {
       if ( apples == 0 )
          continue;            // Don't bother dividing up nothing.
       for ( people = -2 ; people < 4 ; people += 2 )
       {
          if ( people == 0 )
             continue;         // Don't try to divide by zero.

          share = div( apples, people );

          printf( "If there are %+i of us and %+i apples, "
                  "we each get %+i with %+i left over.\n",
                   people, apples, share.quot, share.rem );
       }
   }
   return 0;
}
