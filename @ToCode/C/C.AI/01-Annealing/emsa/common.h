/*
 *  Simulated Annealing Symbolics and Function Prototypes
 *
 *  ./software/ch2/emsa/common.h
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdlib.h>

#define MAX_LENGTH	30

typedef int solutionType[MAX_LENGTH];

typedef struct {
  solutionType solution;
  float energy;
} memberType;

/* Annealing Schedule */
#define INITIAL_TEMPERATURE	30.0
#define FINAL_TEMPERATURE	0.5
#define ALPHA			0.99
#define STEPS_PER_CHANGE	100

/* Return a random number between 0 and 1 */
#define getSRand()	((float)rand() / (float)RAND_MAX)

/* Return an integer from 0..(x-1) */
#define getRand(x)	(int)((x) * getSRand())
