/*
 * Backpropagation Algorithm
 */

#include <stdio.h>
#include "neuroController.h"

int main()
{
   double err;
   int i, sample = 0, iterations = 0;
   int sum = 0;

   out = fopen("stats.txt", "w");

   /* Seed the random number generator */
   srand(time(NULL)); // NOLINT(*-msc51-cpp)

   assignRandomWeights();

   while (1)
   {
      if (++sample == MAX_SAMPLES)
      {
         sample = 0;
      }

      inputs[0] = samples[sample].health;
      inputs[1] = samples[sample].knife;
      inputs[2] = samples[sample].gun;
      inputs[3] = samples[sample].enemy;

      target[0] = samples[sample].out[0];
      target[1] = samples[sample].out[1];
      target[2] = samples[sample].out[2];
      target[3] = samples[sample].out[3];

      feedForward();

      /* need to iterate through all ... */

      err = 0.0;
      for (i = 0; i < OUTPUT_NEURONS; i++)
      {
         err += sqr((samples[sample].out[i] - actual[i]));
      }

      err = 0.5 * err;

      fprintf(out, "%g\n", err);
      printf("mse = %g\n", err);

      if (iterations++ > 100000)
      {
         break;
      }

      backPropagate();
   }

   /* Test the network */
   for (i = 0; i < MAX_SAMPLES; i++)
   {
      inputs[0] = samples[i].health;
      inputs[1] = samples[i].knife;
      inputs[2] = samples[i].gun;
      inputs[3] = samples[i].enemy;

      target[0] = samples[i].out[0];
      target[1] = samples[i].out[1];
      target[2] = samples[i].out[2];
      target[3] = samples[i].out[3];

      feedForward();

      if (action(actual) != action(target))
      {

         printf("%2.1g:%2.1g:%2.1g:%2.1g %s (%s)\n",
                inputs[0], inputs[1], inputs[2], inputs[3],
                strings[action(actual)], strings[action(target)]);

      }
      else
      {
         sum++;
      }
   }

   printf("Network is %g%% correct\n",
          ((float) sum / (float) MAX_SAMPLES) * 100.0);

   /* Run some tests */

   /*  Health            Knife            Gun              Enemy */
   inputs[0] = 2.0;
   inputs[1] = 1.0;
   inputs[2] = 1.0;
   inputs[3] = 1.0;
   feedForward();
   printf("2111 Action %s\n", strings[action(actual)]);

   inputs[0] = 1.0;
   inputs[1] = 1.0;
   inputs[2] = 1.0;
   inputs[3] = 2.0;
   feedForward();
   printf("1112 Action %s\n", strings[action(actual)]);

   inputs[0] = 0.0;
   inputs[1] = 0.0;
   inputs[2] = 0.0;
   inputs[3] = 0.0;
   feedForward();
   printf("0000 Action %s\n", strings[action(actual)]);

   inputs[0] = 0.0;
   inputs[1] = 1.0;
   inputs[2] = 1.0;
   inputs[3] = 1.0;
   feedForward();
   printf("0111 Action %s\n", strings[action(actual)]);

   inputs[0] = 2.0;
   inputs[1] = 0.0;
   inputs[2] = 1.0;
   inputs[3] = 3.0;
   feedForward();
   printf("2013 Action %s\n", strings[action(actual)]);

   inputs[0] = 2.0;
   inputs[1] = 1.0;
   inputs[2] = 0.0;
   inputs[3] = 3.0;
   feedForward();
   printf("2103 Action %s\n", strings[action(actual)]);

   inputs[0] = 0.0;
   inputs[1] = 1.0;
   inputs[2] = 0.0;
   inputs[3] = 3.0;
   feedForward();
   printf("0103 Action %s\n", strings[action(actual)]);

   fclose(out);

   return 0;
}
