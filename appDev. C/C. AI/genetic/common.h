/*
 * Common Symbolics and Prototypes
 */

#ifndef GENETIC_COMMON_H
#define GENETIC_COMMON_H

#include <stdlib.h>
#include <stdio.h>

/* Genetic Algorithm Parameters */

#define CROSSOVER_PROB		0.8
#define MUTATION_PROB		0.02
#define MAX_GENERATIONS		10000
#define COUNT			10

#define MAX_CHROMS		3000
#define MAX_PROGRAM		6


/* Function Macros and Prototypes */

#define getSRand()	((float)rand() / (float)RAND_MAX)
#define getRand(x)	(int)((x) * getSRand())

int interpretSTM( const int *, int, const int *, int );

int performFitnessCheck ( FILE * );

int performSelection( void );

typedef struct population {
   float fitness;
   int   progSize;
   int   program[MAX_PROGRAM];
} POPULATION_TYPE;

#define TIER1   1                           // 1
#define TIER2   ((TIER1+1) * COUNT)         // 10
#define TIER3   ((TIER1+TIER2+2) * COUNT)   // 65
#define MAX_FIT (float)((TIER3 * COUNT) + (TIER2 * COUNT) + (TIER1 * COUNT))


/* Virtual Computer Symbolics */

#define DUP			0x00
#define SWAP			0x01
#define MUL			0x02
#define ADD			0x03
#define OVER			0x04
#define NOP			0x05

#define MAX_INSTRUCTION		(NOP+1)

#define NONE			0
#define STACK_VIOLATION		1
#define MATH_VIOLATION		2

#endif //GENETIC_COMMON_H
