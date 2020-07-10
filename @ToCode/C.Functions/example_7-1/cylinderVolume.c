// Example 7-1. Function cylinderVolume()
// cylinderVolume.c

// The cylinderVolume() function calculates the volume of a cylinder.
// Arguments: Radius of the base circle; height of the cylinder.
// Return value: Volume of the cylinder.

extern double cylinderVolume( double r, double h )
{
   const double pi = 3.1415926536; // Pi is constant
   return pi * r * r * h;
}

#include <stdio.h>

int main()
{
   double radius = 0.3, height = 5.0;

   printf( "A cylinder: \n"
           "  Radius of base circle:  %6.2f\n", radius );
   printf( "  Height of the cylinder: %6.2f\n", height );
   printf( "  Volume of the cylinder: %6.2f\n", 
                                      cylinderVolume( radius, height) );
   return 0;
}
