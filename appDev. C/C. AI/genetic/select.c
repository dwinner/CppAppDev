//
// Genetic Algorithm Selection Algorithm
//

#include <stdio.h>
#include "common.h"

#define XPROB		(1.0 - CROSSOVER_PROB)
#define MPROB		(1.0 - MUTATION_PROB)

#define MAX(a,b)	((a > b) ? a : b)

extern POPULATION_TYPE populations[2][MAX_CHROMS];
extern int curPop;

extern float maxFitness;
extern float avgFitness;
extern float minFitness;

int    curMutations, curCrossovers;


/*
 *  selectParent()
 *
 *  This function selects a parent from the current generation using
 *  a form of the roulette-wheel selection method.
 *
 */

int selectParent( void )
{
   static int chrom = 0;
   int ret = -1;
   float retFitness = 0.0;

   do {

      retFitness = (populations[curPop][chrom].fitness / maxFitness);

      if (chrom == MAX_CHROMS) chrom = 0;

      if (populations[curPop][chrom].fitness > minFitness) {
         if (getSRand() < retFitness) {
            ret = chrom++;
            retFitness = populations[curPop][chrom].fitness;
            break;
         }
      }

      chrom++;

   } while (1);

   return ret;
}


/*
 *  performReproduction()
 *
 *  This function performs the actual reproduction.  Given two parents
 *  and two children, the parents are recombined into the two children
 *  in the next generation.  If crossover is to be performed, a
 *  crossover point is selected (the point at which the parent's
 *  chromosomes tail's will be split to the two children).  The mutation
 *  operator may also be performed, on each gene as it's copied from
 *  the parent to the child.
 *
 */

int performReproduction( int parentA, int parentB, int childA, int childB )
{
   int crossPoint, i;
   int nextPop = (curPop == 0) ? 1 : 0;

   int mutate( int );

   if (getSRand() > XPROB) {
      crossPoint = getRand(MAX(populations[curPop][parentA].progSize-2,
                               populations[curPop][parentB].progSize-2))+1;
      curCrossovers++;
   } else {
      crossPoint = MAX_PROGRAM;
   }

   for (i = 0 ; i < crossPoint ; i++) {
      populations[nextPop][childA].program[i] =
          mutate(populations[curPop][parentA].program[i]);
      populations[nextPop][childB].program[i] =
          mutate(populations[curPop][parentB].program[i]);
   }

   for ( ; i < MAX_PROGRAM ; i++) {
      populations[nextPop][childA].program[i] =
          mutate(populations[curPop][parentB].program[i]);
      populations[nextPop][childB].program[i] =
          mutate(populations[curPop][parentA].program[i]);
   }

   populations[nextPop][childA].progSize =
       populations[curPop][parentA].progSize;
   populations[nextPop][childB].progSize =
       populations[curPop][parentB].progSize;

   return 0;
}


/*
 *  mutate()
 *
 *  This function returns a random instruction mimicing the process
 *  of mutation.  The current gene of the chromosome is passed in,
 *  which could be used to create the new chromosome (as a random
 *  bit replacement).  This function currently does not use it.
 *
 */

int mutate(int gene)
{
   float temp = getSRand();
   if (temp > MPROB) {
      gene = getRand(MAX_INSTRUCTION);
      curMutations++;
   }
   return gene;
}


/*
 *  performSelection()
 *
 *  This function selects two parents from the current population and
 *  recombines them into two children for the next generation.  The
 *  process of recombination includes both crossover and mutation
 *  (dependent upon the probabilities for each).
 *
 */

int performSelection( void )
{
   int par1, par2;
   int child1, child2;
   int chrom;

   for (chrom = 0 ; chrom < MAX_CHROMS ; chrom+=2) {

      par1 = selectParent();
      par2 = selectParent();

      child1 = chrom;
      child2 = chrom+1;

      performReproduction( par1, par2, child1, child2 );

   }
   return 0;
}
