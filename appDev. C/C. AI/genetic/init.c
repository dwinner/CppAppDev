//
// Genetic Algorithm Population Initialization
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "common.h"

POPULATION_TYPE populations[2][MAX_CHROMS];

int curPop;

/*
 *  initMember()
 *
 *  Initialize a single member in the population.  This includes the
 *  initial fitness, program size and the initial set of random
 *  instructions.
 *
 */

void initMember(int pop, int index )
{
   int progIndex;

   populations[pop][index].fitness = 0.0;
   populations[pop][index].progSize = MAX_PROGRAM-1;

   progIndex = 0;
   while (progIndex < MAX_PROGRAM) {
      populations[pop][index].program[progIndex++] = getRand(MAX_INSTRUCTION);
   }

}


/*
 *  initPopulation()
 *
 *  Initialize all of the chromosomes in the population (potential
 *  solutions to the given problem).
 *
 */

void initPopulation( void )
{
   int index;

   for (index = 0 ; index < MAX_CHROMS ; index++) {
      initMember(curPop, index);
   }
}
