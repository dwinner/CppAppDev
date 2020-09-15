// Example 1-3. The second source file, containing the circularArea() function
//
// circulararea.c: Calculates the areas of circles.
// Called by main() in circle.c
// Parameter: The radius of the circle
// Return value: The area of the circle

double circularArea(double r)      // Definition of circularArea() begins
{
   const double pi = 3.1415926536;   // Pi is a constant
   return pi * r * r;
}
