/**
 * Definition and usage of generic macro
 * for math functions
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define RAD_TO_DEG (180/(4*atanl(1)))

/**
 * Generic sqrt function
 */
#define SQRT(X) _Generic((X),\
   long double:   sqrtl,\
   default:       sqrt,\
   float:         sqrtf\
)(X)

/**
 * Generic sin function for degrees
 */
#define SIN(X) _Generic((X),\
   long double:   sinl((X)/RAD_TO_DEG),\
   default:       sin((X)/RAD_TO_DEG),\
   float:         sinf((X)/RAD_TO_DEG)\
)

int main()
{
   float x = 45.0f;
   double xx = 45.0;
   long double xxx = 45.0L;

   long double y = SQRT(x);
   long double yy = SQRT(xx);
   long double yyy = SQRT(xxx);

   printf("%.17Lf\n", y);   // float version
   printf("%.17Lf\n", yy);  // default version
   printf("%.17Lf\n", yyy); // long double version

   int i = 45;
   yy = SQRT(i); // default version
   printf("%.17Lf\n", yy);
   yyy = SIN(xxx);  // long double version
   printf("%.17Lf\n", yyy);

   return EXIT_SUCCESS;
}
