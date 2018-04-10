/**
 * Population-based Simulated Annealing Implementation for n-Queens
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "emsapop.h"
#include <stdlib.h>

int main()
{
   return 0;
}

void initializePopulation()
{
   int index, member;

   for (member = 0; member < MAX_MEMBERS; member++)
   {
      /* Initial setup of the solution */
      for (index = 0; index < MAX_LENGTH; index++)
      {
         Population[member].solution[index] = index + 1;
      }

      /* Randomly perturb the solution */
      for (index = 0; index < MAX_LENGTH; index++)
      {
         const int x = GET_RAND(MAX_LENGTH);
         const int temp = Population[member].solution[index];
         Population[member].solution[index] = Population[member].solution[x];
         Population[member].solution[x] = temp;
      }
   }
}

void tweakSolution(Member_type* member)
{
   int temp, x, y;

   x = GET_RAND(MAX_LENGTH);
   do
   {
      y = GET_RAND(MAX_LENGTH);
   }
   while (x==y);

   temp = member->solution[x];
   member->solution[x] = member->solution[y];
   member->solution[y] = temp;
}
