/**
 * Depth search of destination
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
