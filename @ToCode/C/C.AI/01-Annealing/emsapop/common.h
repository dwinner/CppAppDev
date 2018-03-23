/*
 *  Population-based Simulated Annealing Symbolics and Function Prototypes
 *
 *  ./software/ch2/emsapop/common.h
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdlib.h>

#define MAX_LENGTH	80

typedef char solutionType[MAX_LENGTH];

typedef struct {
  solutionType solution;
  float energy;
} memberType;

#define MAX_MEMBERS	100

/* Annealing Schedule */
#define INITIAL_TEMPERATURE	10.0
#define FINAL_TEMPERATURE	0.0
#define RATE			0.05
#define STEPS_PER_CHANGE	100

/* Return a random number between 0 and 1 */
#define getSRand()	((float)rand() / (float)RAND_MAX)

/* Return an integer from 0..(x-1) */
#define getRand(x)	(int)((x) * getSRand())
