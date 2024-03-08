/**
 * The shortest distance:
 * Optimal solution using least-cost with route removal.
 */

#include "sd.h"

#include <stdio.h>

int main()
{
   char from[20], to[20];
   int t, d;

   setup();

   printf("From? ");
   gets(from);
   printf("To? ");
   gets(to);
   do
   {
      isflight(from, to);
      d = route();
      tos = 0;  /* reset the backtrack stack */
   }
   while (d != 0);  /* while still finding solutions */

   t = 0;
   printf("Optimal solution is:\n");
   while (t < stos)
   {
      printf("%s to ", solution[t].from);
      d += solution[t].dist;
      t++;
   }

   printf("%s\n", to);
   printf("Distance is %d.\n", d);

   return 0;
}
