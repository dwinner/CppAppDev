﻿/**
 * Displaying the value of a union in both member data types
 * 
 */

#include <stdio.h>

// number union definition
union number
{
   int x;
   double y;
};

int main(void)
{
   union number value; // define union variable

   value.x = 100; // put an integer into the union
   printf("%s\n%s\n%s\n  %d\n\n%s\n  %f\n\n\n",
          "Put 100 in the integer member",
          "and print both members.",
          "int:", value.x,
          "double:", value.y);

   value.y = 100.1; // put a double into the same union
   printf("%s\n%s\n%s\n  %d\n\n%s\n  %f\n",
          "Put 100.0 in the floating member",
          "and print both members.",
          "int:", value.x,
          "double:", value.y);

   return 0;
}
