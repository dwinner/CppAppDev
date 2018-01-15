/**
 * Floating-point comparisons
 */

#include <math.h>
#include <stdio.h>

int main(void)
{
   const double ANSWER = 3.14159;
   double response;

   printf("What is the value of pi?\n");
   scanf_s("%lf", &response);
   while (fabs(response - ANSWER) > 0.0001)
   {
      printf("Try again!\n");
      scanf_s("%lf", &response);
   }
   printf("Close enough!\n");

   return 0;
}
