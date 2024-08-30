#include "neuroController.h"

double wih[INPUT_NEURONS + 1][HIDDEN_NEURONS];
double who[HIDDEN_NEURONS + 1][OUTPUT_NEURONS];
double inputs[INPUT_NEURONS];
double hidden[HIDDEN_NEURONS];
double target[OUTPUT_NEURONS];
double actual[OUTPUT_NEURONS];
double erro[OUTPUT_NEURONS];
double errh[HIDDEN_NEURONS];
FILE *out;

ElementT samples[MAX_SAMPLES] =
    {
        {2.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0}},
        {2.0, 0.0, 0.0, 1.0, {0.0, 0.0, 1.0, 0.0}},
        {2.0, 0.0, 1.0, 1.0, {1.0, 0.0, 0.0, 0.0}},
        {2.0, 0.0, 1.0, 2.0, {1.0, 0.0, 0.0, 0.0}},
        {2.0, 1.0, 0.0, 2.0, {0.0, 0.0, 0.0, 1.0}},
        {2.0, 1.0, 0.0, 1.0, {1.0, 0.0, 0.0, 0.0}},

        {1.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0}},
        {1.0, 0.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0}},
        {1.0, 0.0, 1.0, 1.0, {1.0, 0.0, 0.0, 0.0}},
        {1.0, 0.0, 1.0, 2.0, {0.0, 0.0, 0.0, 1.0}},
        {1.0, 1.0, 0.0, 2.0, {0.0, 0.0, 0.0, 1.0}},
        {1.0, 1.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0}},

        {0.0, 0.0, 0.0, 0.0, {0.0, 0.0, 1.0, 0.0}},
        {0.0, 0.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0}},
        {0.0, 0.0, 1.0, 1.0, {0.0, 0.0, 0.0, 1.0}},
        {0.0, 0.0, 1.0, 2.0, {0.0, 1.0, 0.0, 0.0}},
        {0.0, 1.0, 0.0, 2.0, {0.0, 1.0, 0.0, 0.0}},
        {0.0, 1.0, 0.0, 1.0, {0.0, 0.0, 0.0, 1.0}}
    };

char *strings[4] =
    {
        "Attack",
        "Run",
        "Wander",
        "Hide"
    };

void assignRandomWeights(void)
{
   int hid, inp, lOut;
   for (inp = 0; inp < INPUT_NEURONS + 1; inp++)
   {
      for (hid = 0; hid < HIDDEN_NEURONS; hid++)
      {
         wih[inp][hid] = RAND_WEIGHT; // NOLINT(*-msc50-cpp)
      }
   }

   for (hid = 0; hid < HIDDEN_NEURONS + 1; hid++)
   {
      for (lOut = 0; lOut < OUTPUT_NEURONS; lOut++)
      {
         who[hid][lOut] = RAND_WEIGHT; // NOLINT(*-msc50-cpp)
      }
   }
}

double sigmoid(double val)
{
   return (1.0 / (1.0 + exp(-val)));
}

double sigmoidDerivative(double val)
{
   return (val * (1.0 - val));
}

void feedForward()
{
   int inp, hid, lOut;
   double sum;

   /* Calculate input to hidden layer */
   for (hid = 0; hid < HIDDEN_NEURONS; hid++)
   {
      sum = 0.0;
      for (inp = 0; inp < INPUT_NEURONS; inp++)
      {
         sum += inputs[inp] * wih[inp][hid];
      }

      /* Add in Bias */
      sum += wih[INPUT_NEURONS][hid];

      hidden[hid] = sigmoid(sum);
   }

   /* Calculate the hidden to output layer */
   for (lOut = 0; lOut < OUTPUT_NEURONS; lOut++)
   {
      sum = 0.0;
      for (hid = 0; hid < HIDDEN_NEURONS; hid++)
      {
         sum += hidden[hid] * who[hid][lOut];
      }

      /* Add in Bias */
      sum += who[HIDDEN_NEURONS][lOut];

      actual[lOut] = sigmoid(sum);
   }
}

void backPropagate(void)
{
   int inp, hid, lOut;

   /* Calculate the output layer error (step 3 for output cell) */
   for (lOut = 0; lOut < OUTPUT_NEURONS; lOut++)
   {
      erro[lOut] = (target[lOut] - actual[lOut]) * sigmoidDerivative(actual[lOut]);
   }

   /* Calculate the hidden layer error (step 3 for hidden cell) */
   for (hid = 0; hid < HIDDEN_NEURONS; hid++)
   {
      errh[hid] = 0.0;
      for (lOut = 0; lOut < OUTPUT_NEURONS; lOut++)
      {
         errh[hid] += erro[lOut] * who[hid][lOut];
      }

      errh[hid] *= sigmoidDerivative(hidden[hid]);
   }

   /* Update the weights for the output layer (step 4 for output cell) */
   for (lOut = 0; lOut < OUTPUT_NEURONS; lOut++)
   {
      for (hid = 0; hid < HIDDEN_NEURONS; hid++)
      {
         who[hid][lOut] += (LEARN_RATE * erro[lOut] * hidden[hid]);
      }

      /* Update the Bias */
      who[HIDDEN_NEURONS][lOut] += (LEARN_RATE * erro[lOut]);
   }

   /* Update the weights for the hidden layer (step 4 for hidden cell) */
   for (hid = 0; hid < HIDDEN_NEURONS; hid++)
   {
      for (inp = 0; inp < INPUT_NEURONS; inp++)
      {
         wih[inp][hid] += (LEARN_RATE * errh[hid] * inputs[inp]);
      }

      /* Update the Bias */
      wih[INPUT_NEURONS][hid] += (LEARN_RATE * errh[hid]);
   }
}

int action(const double *vector)
{
   int index, sel;
   double max;

   sel = 0;
   max = vector[sel];

   for (index = 1; index < OUTPUT_NEURONS; index++)
   {
      if (vector[index] > max)
      {
         max = vector[index];
         sel = index;
      }
   }

   return (sel);
}