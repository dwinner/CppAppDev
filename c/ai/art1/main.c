/**
 * Application of ART (Adaptive Resonance Theory) to personalization.
 *
 * Initialize, perform the ART1 algorithm, display the customer data and
 * then make a recommendation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "artPers.h"

int main()
{
   int customer;

   srand(time(NULL)); // NOLINT(*-msc51-cpp)

   init();
   performArt1();
   displayCustomerDb();

   for (customer = 0; customer < MAX_CUSTOMERS; customer++)
   {
      makeRecommendation(customer);
   }

   return 0;
}
