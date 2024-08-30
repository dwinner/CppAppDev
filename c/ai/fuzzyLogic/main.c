/*
 * Main function for the Fuzzy Logic Battery Charge Control Simulator
 */

#include <stdio.h>
#include "simulate.h"

int main()
{
   int i;
   for (i = 0; i < 3000; i++)
   {
      simulate();
      chargeControl(&timer);
      timer += 1.0F;
      printf("%d, %f, %f, %d\n",
             i,
             voltage,
             temperature,
             chargeMode
      );
   }

   return 0;
}
