// erf_ex.c : erf() example
// -------------------------------------------------------------
// double erf( double x );
// float erff( float x );
// long double erfl( long double x );

#include <math.h>
#include <stdio.h>

/*
 * Given a normal distribution with mean 0 and standard deviation 1,
 * calculate the probability that the random variable is within the
 * range [0, 1.125]
 */

int main()
{
   double sigma = 1.0;     // The standard deviation
   double bound = 1.125;
   double probability;     // probability that mean <= value <= bound

   probability = 0.5 * erf(bound / (sigma * sqrt(2.0)));

   printf("Given a normal distribution with mean 0 and standard deviation 1,\n"
          "the probability that a random variable is within the range [0, 1.125]\n"
          "is %lf.\n", probability);

   return 0;
}
