#ifndef BACKPROPAGTION_NEUROCONTROLLER_H
#define BACKPROPAGTION_NEUROCONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT_NEURONS      4
#define HIDDEN_NEURONS      3
#define OUTPUT_NEURONS      4

/************************************************************
 * Weight Structures
 ************************************************************/

/**
 * @brief Input to Hidden Weights (with Biases)
 */
extern double wih[INPUT_NEURONS + 1][HIDDEN_NEURONS];

/**
 * @brief Hidden to Output Weights (with Biases)
 */
extern double who[HIDDEN_NEURONS + 1][OUTPUT_NEURONS];

/************************************************************
 * Activations
 ************************************************************/
extern double inputs[INPUT_NEURONS];
extern double hidden[HIDDEN_NEURONS];
extern double target[OUTPUT_NEURONS];
extern double actual[OUTPUT_NEURONS];

/************************************************************
 * Unit Errors
 ************************************************************/
extern double erro[OUTPUT_NEURONS];
extern double errh[HIDDEN_NEURONS];

extern FILE *out;

#define sqr(x)   ((x) * (x))
#define LEARN_RATE      0.2
#define RAND_WEIGHT   ( ((float)rand() / (float)RAND_MAX) - 0.5)
#define getSRand()   ((float)rand() / (float)RAND_MAX)
#define getRand(x)   (int)((x) * getSRand())
#define MAX_SAMPLES 18

typedef struct
{
   double health;
   double knife;
   double gun;
   double enemy;
   double out[OUTPUT_NEURONS];
} ElementT;

/**
 * @brief The initial model to learn
 */
extern ElementT samples[MAX_SAMPLES];

extern char *strings[4];

/**
 * @brief Assign a set of random weights to the network.
 */
void assignRandomWeights(void);

/**
 * @brief Calculate and return the sigmoid of the val argument.
 * @param val Value to sigmoid
 * @return Sigmoid of the value
 */
double sigmoid(double val);

/**
 * @brief Calculate and return the derivative of the sigmoid for the val argument.
 * @param val Value to derivative sigmoid
 * @return Derivative sigmoid
 */
double sigmoidDerivative(double val);

/**
 * @brief Feedforward the inputs of the neural network to the outputs.
 */
void feedForward(void);

/**
 * @brief Back propagate the error through the network.
 */
void backPropagate(void);

/**
 * @brief Select an action using winner-takes-all network strategy.
 * @param vector Network-like vector
 * @return Action ID
 */
int action(const double *vector);

#endif //BACKPROPAGTION_NEUROCONTROLLER_H
