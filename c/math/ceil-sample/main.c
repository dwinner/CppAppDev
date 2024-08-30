// ceil_ex.c : ceil() example
// -------------------------------------------------------------

#include <math.h>
// double ceil( double x );
// float ceilf( float x );
// long double ceill( long double x );
#include <stdio.h>
#include <stdlib.h>

int main()
{
   /* Amount due = unit price * count * VAT, rounded up to the next cent */

   div_t total = {0, 0};
   int count = 17;
   int price = 9999;                  // 9999 cents is $99.99
   double vat_rate = 0.055;           // Value-added tax of 5.5%

   total = div((int) ceil((count * price) * (1 + vat_rate)), 100);
   printf("Total due: $%d.%2d\n", total.quot, total.rem);

   return 0;
}
