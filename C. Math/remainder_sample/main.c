// remainder_ex.c : remainder() example
// -------------------------------------------------------------
// double remainder( double x, double y );
// float remainderf( float x, float y );
// long double remainderl( long double x, long double y );

#include <math.h>
#include <stdio.h>

int main()
{
   double apples = 0.0, people = 0.0, share = 0.0, left = 0.0;

   printf("\nHow many people? ");
   scanf("%lf", &people);

   printf("\nHow many apples? ");
   scanf("%lf", &apples);

   left = remainder(apples, people);     // left may be negative!
   share = (apples - left) / people;

   printf("If there are %.1lf of us and %.1lf apples, "
          "each of us gets %.1lf of %s, with %.1lf left over.\n",
          people, apples, share, (share < 1) ? "one" : "them", left);

   return 0;
}
