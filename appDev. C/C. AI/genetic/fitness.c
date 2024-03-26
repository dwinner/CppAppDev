#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Genetic Algorithm Fitness Evaluation Functions (user-defined)
//

#include <stdlib.h>
#include <stdio.h>
#include "common.h"

extern PopulationT populations[2][MAX_CHROMOSOMES];
extern int curPop;

float maxFitness;
float avgFitness;
float minFitness;

/*
 * NOTE: This function is different for each problem to be solved...
 */

extern int stackPointer;
extern int stack[];

static int x = 0;
float totFitness;

/**
 * @brief Perform fitness check
 * @param outP out file
 * @return Always 0
 */
int performFitnessCheck(FILE *outP)
{
   int chromosome, result, i;
   int args[10], answer;

   maxFitness = 0.0F;
   avgFitness = 0.0F;
   minFitness = 1000.0F;
   totFitness = 0.0F;

   for (chromosome = 0; chromosome < MAX_CHROMOSOMES; chromosome++)
   {
      populations[curPop][chromosome].fitness = 0.0F;

      for (i = 0; i < COUNT; i++)
      {
         args[0] = (rand() & 0x1f) + 1;
         args[1] = (rand() & 0x1f) + 1;
         args[2] = (rand() & 0x1f) + 1;

         /* Problem is xy + y^2 + z */
         answer = (args[0] * args[1]) + (args[1] * args[1]) + args[2];
         result = interpretStm(populations[curPop][chromosome].program,
                               populations[curPop][chromosome].programSize,
                               args, 3);

         if (result == NONE)
         {
            populations[curPop][chromosome].fitness += TIER1;
         }

         if (stackPointer == 1)
         {
            populations[curPop][chromosome].fitness += TIER2;
         }

         if (stack[0] == answer)
         {
            populations[curPop][chromosome].fitness += TIER3;
         }
      }

      if (populations[curPop][chromosome].fitness > maxFitness)
      {
         maxFitness = populations[curPop][chromosome].fitness;
      }
      else if (populations[curPop][chromosome].fitness < minFitness)
      {
         minFitness = populations[curPop][chromosome].fitness;
      }

      totFitness += populations[curPop][chromosome].fitness;
   }

   avgFitness = totFitness / (float) MAX_CHROMOSOMES;

   if (outP)
   {
      fprintf(outP, "%d %6.4f %6.4f %6.4f\n",
              x++, minFitness, avgFitness, maxFitness);
   }

   return 0;
}

#pragma clang diagnostic pop