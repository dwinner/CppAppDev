/**
 * Depth-first with multiple solutions using node removal
 *
 */

#include "removal.h"
#include <stdio.h>

int main()
{
   char from[20], to[20], c1[20], c2[20];
   int d;

   setup();

   printf("From? ");
   gets(from);
   printf("To? ");
   gets(to);
   do
   {
      isFlight(from, to);
      route(to);
      clearMarkers(); /* reset the database */
      if (stackTop > 0) pop(c1, c2, &d);
      retract(c1, c2); /* remove last node from database */
      stackTop = 0;    /* reset the backtrack stack */
   } while (getchar() != 'q');

   return 0;
}
