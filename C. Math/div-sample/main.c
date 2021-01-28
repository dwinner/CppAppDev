/**
 * div_ex.c : div() example:
 * div_t div(int dividend, int divisor );
 * ldiv_t ldiv( long dividend, long divisor );
 * lldiv_t lldiv( long long dividend, long long divisor );
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
   int people, apples;
   div_t share;

   for (apples = -3; apples < 6; apples += 3)
   {
      // Don't bother dividing up nothing.
      if (apples == 0)
      {
         continue;
      }

      for (people = -2; people < 4; people += 2)
      {
         // Don't try to divide by zero.
         if (people == 0)
         {
            continue;
         }

         share = div(apples, people);

         printf("If there are %+i of us and %+i apples, "
                "we each get %+i with %+i left over.\n",
                people, apples, share.quot, share.rem);
      }
   }

   return 0;
}
