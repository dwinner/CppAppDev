/**
 * The recursive function power() calculates
 * integer powers of floating-point numbers
 */

/**
 * Power function
 * @param base  Number
 * @param exp   Power degree
 * @return Power of Number
 */
double power(double base, unsigned int exp)
{
   return exp == 0
          ? 1.0
          : base * power(base, exp - 1);
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
   printf("2.2 to the power of 3 is %.4f\n", power(2.2, 3));
   return EXIT_SUCCESS;
}
