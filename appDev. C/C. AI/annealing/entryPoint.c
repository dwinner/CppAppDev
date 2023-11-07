/**
 * Population-based Simulated Annealing Implementation for n-Queens
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "emsapop.h"

extern Member_type Population[MAX_MEMBERS];

int main()
{
   int solution = -1;
   double temperature = INITIAL_TEMPERATURE;
   srand(time(NULL));
   InitializePopulation();
   ComputeAllEnergy();

   while (temperature > FINAL_TEMPERATURE)
   {
      printf("temperature %f (solution %d)\n",
             temperature,
             solution);

      for (int step = 0; step < STEPS_PER_CHANGE; step++)
      {
         solution = SimulateAnnealing(temperature);
      }

      temperature -= RATE;
   }

   if (solution == -1)
   {
      printf("No solution found\n");
   }
   else
   {
      EmitSolution(&Population[solution]);
   }

   return EXIT_SUCCESS;
}
