// Example 1-1. A simple C program
// circle.c: Calculate and print the areas of circles

#include <stdio.h>                 // Preprocessor directive

double circularArea( double r );   // Function declaration (prototype form)

int main()                         // Definition of main() begins
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

// The function circularArea() calculates the area of a circle
// Parameter: The radius of the circle
// Return value: The area of the circle

double circularArea( double r )      // Definition of circularArea() begins
{
   const double pi = 3.1415926536;   // Pi is a constant
   return pi * r * r;
}
