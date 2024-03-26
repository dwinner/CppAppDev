#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Genetic Algorithm Selection Algorithm
//

#include "common.h"

#define X_PROB      (1.0 - CROSSOVER_PROB)
#define M_PROB      (1.0 - MUTATION_PROB)

#define MAX(a, b)   ((a > b) ? a : b)

extern PopulationT populations[2][MAX_CHROMOSOMES];
extern int curPop;

extern float maxFitness;
extern float avgFitness;
extern float minFitness;

int curMutations, curCrossovers;

static int mutate(int gene);

/**
 * @brief This function selects a parent from the current generation using
 * a form of the roulette-wheel selection method.
 * @return chromosome count
 */
int selectParent(void)
{
   static int chromosome = 0;
   int returnValue;
   float retFitness;

   do
   {
      retFitness = (populations[curPop][chromosome].fitness / maxFitness);
      if (chromosome == MAX_CHROMOSOMES)
      {
         chromosome = 0;
      }

      if (populations[curPop][chromosome].fitness > minFitness
          && getSRand() < retFitness)
      {
         returnValue = chromosome++;
         // retFitness = populations[curPop][chromosome].fitness;
         break;
      }

      chromosome++;
   }
   while (1);

   return returnValue;
}

/**
 * @brief Perform the reproduction
 * @details This function performs the actual reproduction.  Given two parents
 *  and two children, the parents are recombined into the two children
 *  in the next generation.  If crossover is to be performed, a
 *  crossover point is selected (the point at which the parent's
 *  chromosomes tail's will be split to the two children).  The mutation
 *  operator may also be performed, on each gene as it's copied from
 *  the parent to the child.
 * @param parentA
 * @param parentB
 * @param childA
 * @param childB
 * @return
 */
int performReproduction(int parentA, int parentB, int childA, int childB)
{
   int crossPoint, i;
   int nextPop = (curPop == 0) ? 1 : 0;

   // int mutate(int);

   if (getSRand() > X_PROB)
   {
      crossPoint = getRand(MAX(populations[curPop][parentA].programSize - 2,
                               populations[curPop][parentB].programSize - 2)) + 1;
      curCrossovers++;
   }
   else
   {
      crossPoint = MAX_PROGRAM;
   }

   for (i = 0; i < crossPoint; i++)
   {
      populations[nextPop][childA].program[i] =
          mutate(populations[curPop][parentA].program[i]);
      populations[nextPop][childB].program[i] =
          mutate(populations[curPop][parentB].program[i]);
   }

   for (; i < MAX_PROGRAM; i++)
   {
      populations[nextPop][childA].program[i] =
          mutate(populations[curPop][parentB].program[i]);
      populations[nextPop][childB].program[i] =
          mutate(populations[curPop][parentA].program[i]);
   }

   populations[nextPop][childA].programSize =
       populations[curPop][parentA].programSize;
   populations[nextPop][childB].programSize =
       populations[curPop][parentB].programSize;

   return 0;
}

/**
 * @brief This function returns a random instruction mimicking the process
 *  of mutation. The current gene of the chromosome is passed in,
 *  which could be used to create the new chromosome (as a random
 *  bit replacement). This function currently does not use it.
 * @param gene Gene ID
 * @return Random selected gene
 */
int mutate(int gene)
{
   float temp = getSRand();
   if (temp > M_PROB)
   {
      gene = getRand(MAX_INSTRUCTION);
      curMutations++;
   }

   return gene;
}

/**
 * @brief Perform the selection
 * @details This function selects two parents from the current population and
 *  recombines them into two children for the next generation. The
 *  process of recombination includes both crossover and mutation
 *  (dependent upon the probabilities for each).
 * @return Always 0
 */
int performSelection(void)
{
   int par1, par2;
   int child1, child2;
   int chromosome;

   for (chromosome = 0; chromosome < MAX_CHROMOSOMES; chromosome += 2)
   {

      par1 = selectParent();
      par2 = selectParent();

      child1 = chromosome;
      child2 = chromosome + 1;

      performReproduction(par1, par2, child1, child2);
   }

   return 0;
}

#pragma clang diagnostic pop