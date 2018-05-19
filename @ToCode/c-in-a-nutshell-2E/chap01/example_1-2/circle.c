// Example 1-2. The first source file, containing the main() function
// circle.c: Prints the areas of circles.
// Uses circulararea.c for the math

#include <stdio.h>
double circularArea( double r );     // Function declaration

int main()
{
   double radius = 1.0, area = 0.0;

   printf( " Areas of Circles\n\n" );
   printf( " Radius              Area\n"
           "-------------------------\n" );

   area = circularArea( radius );
   printf( "%10.1f %10.2f\n", radius, area );

   radius = 5.0;
   area = circularArea( radius );
   printf( "%10.1f %10.2f\n", radius, area );

   return 0;
}
