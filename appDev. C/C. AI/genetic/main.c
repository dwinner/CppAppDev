#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "common.h"

extern void initPopulation(void);

extern PopulationT populations[2][MAX_CHROMOSOMES];
extern float minFitness, maxFitness, avgFitness;
extern int curCrossovers, curMutations;
extern int curPop;

static void printProgram(int index, int popIndex);

/**
 * @brief This is the main function for the genetic algorithm simulation.
 * @return return code
 */
int main()
{
   int generation = 0, i;
   FILE *fp;

   srand(time(NULL));

   curPop = 0;

   fp = fopen("stats.txt", "w");

   if (fp == NULL)
   {
      exit(-1);
   }

   initPopulation();
   performFitnessCheck(fp);

   while (generation < MAX_GENERATIONS)
   {
      curCrossovers = curMutations = 0;
      performSelection();

      /* Switch the populations */
      curPop = (curPop == 0) ? 1 : 0;
      performFitnessCheck(fp);
      if ((generation++ % 100) == 0)
      {
         printf("Generation %d\n", generation - 1);
         printf("\tmaxFitness = %f (%g)\n", maxFitness, MAX_FIT);
         printf("\tavgFitness = %f\n", avgFitness);
         printf("\tminFitness = %f\n", minFitness);
         printf("\tCrossovers = %d\n", curCrossovers);
         printf("\tMutation   = %d\n", curMutations);
         printf("\tpercentage = %f\n", avgFitness / maxFitness);
      }

      if (generation > (MAX_GENERATIONS * 0.25))
      {
         if ((avgFitness / maxFitness) > 0.98)
         {
            printf("converged\n");
            break;
         }
      }

      if (maxFitness == MAX_FIT)
      {
         printf("found solution\n");
         break;
      }
   }

   printf("Generation %d\n", generation - 1);
   printf("\tmaxFitness = %f (%g)\n", maxFitness, MAX_FIT);
   printf("\tavgFitness = %f\n", avgFitness);
   printf("\tminFitness = %f\n", minFitness);
   printf("\tCrossovers = %d\n", curCrossovers);
   printf("\tMutation   = %d\n", curMutations);
   printf("\tpercentage = %f\n", avgFitness / maxFitness);

   for (i = 0; i < MAX_CHROMOSOMES; i++)
   {
      if (populations[curPop][i].fitness == maxFitness)
      {
         int index;
         printf("Program %3d : ", i);

         for (index = 0; index < populations[curPop][i].programSize; index++)
         {
            printf("%02d ", populations[curPop][i].program[index]);
         }

         printf("\n");
         printf("Fitness %f\n", populations[curPop][i].fitness);
         printf("Program size %d\n\n", populations[curPop][i].programSize);

         printProgram(i, curPop);

         break;
      }
   }

   return 0;
}

/*
 *  This function emits the program for a given chromosome in the defined
 *  population. It is tested code only and is not used in the simulation.
 */

char *tins[] =
    {
        "DUP",
        "SWAP",
        "MUL",
        "ADD",
        "OVER",
        "NOP"
    };

/**
 * @brief Print the program
 * @param index Program index
 * @param popIndex Current pop index
 */
static void printProgram(int index, int popIndex)
{
   int i;

   for (i = 0; i < populations[popIndex][index].programSize; i++)
   {
      printf("%s\n", tins[populations[popIndex][index].program[i]]);
   }
}

#pragma clang diagnostic pop