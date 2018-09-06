// power.c : The recursive function power() calculates
// integer powers of floating-point numbers.
// ---------------------------------------------------

double power( double base, unsigned int exp )
{
   if ( exp == 0 ) return 1.0;
   else return base * power( base, exp-1 );
}

#include <stdio.h>

int main()
{
  printf("2.2 to the power of 3 is %.4f\n", power( 2.2, 3) );
  return 0;
}
