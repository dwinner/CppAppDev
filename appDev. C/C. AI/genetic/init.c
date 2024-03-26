#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
//
// Genetic Algorithm Population Initialization
//

#include <stdlib.h>
#include "common.h"

PopulationT populations[2][MAX_CHROMOSOMES];

int curPop;

/**
 * @brief Init member
 * @details Initialize a single member in the population.  This includes the
 *  initial fitness, program size and the initial set of random
 *  instructions.
 * @param pop pop index
 * @param index 2nd dim index
 */
void initMember(int pop, int index)
{
   int programIdx;

   populations[pop][index].fitness = 0.0F;
   populations[pop][index].programSize = MAX_PROGRAM - 1;

   programIdx = 0;
   while (programIdx < MAX_PROGRAM)
   {
      populations[pop][index].program[programIdx++] = getRand(MAX_INSTRUCTION);
   }
}

/**
 * @brief Init population
 * @details Initialize all of the chromosomes in the population (potential
 *  solutions to the given problem).
 */
void initPopulation(void)
{
   int index;

   for (index = 0; index < MAX_CHROMOSOMES; index++)
   {
      initMember(curPop, index);
   }
}

#pragma clang diagnostic pop