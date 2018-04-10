/**
 * Population-based Simulated Annealing Symbolics and Function prototypes
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

/**
 * \brief 
 */
#define MAX_LENGTH   80

/**
 * \brief Solution type
 */
typedef char Solution_type[MAX_LENGTH];

/**
 * \brief Member type
 */
typedef struct
{
   Solution_type solution;
   float energy;
} Member_type;

/**
 * \brief 
 */
#define MAX_MEMBERS  100

/* Annealing Schedule */
#define INITIAL_TEMPERATURE   10.0
#define FINAL_TEMPERATURE     0.0
#define RATE                 0.05
#define STEPS_PER_CHANGE      100

/**
 * \brief Return a random number between 0 and 1
 */
#define GET_S_RAND()   ((float)rand() / (float)RAND_MAX)

/**
 * \brief Return an integer from 0..(x-1)
 * \param x Threshold value
 */
#define GET_RAND(x)     (int)((x) * GET_S_RAND())

#endif // COMMON_H
