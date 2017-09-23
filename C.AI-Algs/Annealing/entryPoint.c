#include <stdio.h>
#include "commonTypes.h"
#include <stdlib.h>
#include "helpers.h"

/**
 *	Annealing alg
 */

int main(int argc, char* argv[])
{
   int timer = 0, step, solution = 0, useNew, accepted;
   float temperature = INITIAL_TEMPERATURE;
   memberType current, working, best;
   FILE *fp;

   fp = fopen("stats.txt", "w");
   
   //srand(time(NULL));

   initializeSolution(&current);
   computeEnergy(&current);
   best.energy = 100.0;
   copySolution(&working, &current);

   while (temperature > FINAL_TEMPERATURE)
   {
      
   }

   return 0;
}
