/*
 * Ant Algorithm Demonstration.
 * Performs the simulation with the given constraints defined in common.h.
 */

#include "antImpl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   int curTime = 0;
   srand(time(NULL));
   init();

   while (curTime++ < MAX_TIME)
   {
      if (simulateAnts() == 0)
      {
         updateTrails();
         if (curTime != MAX_TIME)
         {
            restartAnts();
         }

         printf("Time is %d (%g)\n", curTime, best);
      }
   }

   printf("best tour %g\n", best);
   printf("\n\n");
   emitDataFile(bestIndex);

   return 0;
}
