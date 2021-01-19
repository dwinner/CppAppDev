/**
 * Selection of generic pre definition
 */

#include <stdio.h>

#define MYTYPE(X) _Generic((X),\
   int: "int",\
   float: "float",\
   double: "double",\
   default: "other"\
)

int main()
{
   int d = 5;

   printf("%s\n", MYTYPE(d));     // d has type int
   printf("%s\n", MYTYPE(2.0 * d)); // 2.0*d has type double
   printf("%s\n", MYTYPE(3L));    // 3L has type other
   printf("%s\n", MYTYPE(&d));    // &d has type other

   return 0;
}