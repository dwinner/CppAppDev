/**
 * Depth search of destination.
 * i.e. input:
 * From? New York
 * To? Los Angeles
 * Result: New York to Chicago to Denver to Los Angeles
 * Distance is 3000.
 */

#include <stdio.h>
#include <stdlib.h>
#include "depth1St.h"

int main()
{
   char from[STR_CAPACITY], to[STR_CAPACITY];

   setup();

   printf("From? ");
   gets(from);
   printf("To? ");
   gets(to);

   isFlight(from, to);
   route(to);

   return EXIT_SUCCESS;
}
