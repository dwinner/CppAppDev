/**
 * Depth-first with multiple solutions using node removal
 *
 */

#include <stdio.h>
#include "removal.h"

int main()
{
   char from[20],to[20], c1[20], c2[20];
   int d;

   setup();

   printf("From? ");
   gets(from);
   printf("To? ");
   gets(to);
   do {
      isflight(from,to);
      route(to);
      clearmarkers(); /* reset the database */
      if(tos > 0) pop(c1,c2,&d);
      retract(c1,c2);  /* remove last node from database */
      tos = 0;  /* reset the backtrack stack */
   } while(getchar() != 'q');

   return 0;
}
