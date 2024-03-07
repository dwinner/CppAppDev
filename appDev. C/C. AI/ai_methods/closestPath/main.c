#include "hillClimbing.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
   char from[20], to[20];

   setup();

   printf("From? ");
   gets(from);
   printf("To? ");
   gets(to);

   isFlight(from, to);
   route(to);

   return EXIT_SUCCESS;
}
