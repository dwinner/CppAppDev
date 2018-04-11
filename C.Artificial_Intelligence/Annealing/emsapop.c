/**
 * Population-based Simulated Annealing Implementation for n-Queens
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "emsapop.h"
#include <stdlib.h>

/**
 * \brief Main function for the simulated annealing demonstration
 * \return Exit status code
 */
int main()
{
   int step, solution = -1;
   float temperature = INITIAL_TEMPERATURE;
   srand(time(NULL));
   initializePopulation();
   computeAllEnergy();

   while (temperature > FINAL_TEMPERATURE)
   {
      printf("temperature %f (solution %d)\n", temperature, solution);

      for (step = 0; step < STEPS_PER_CHANGE; step++)
      {
         solution = simulateAnnealing(temperature);
      }

      temperature -= RATE;
   }

   if (solution == -1)
   {
      printf("No solution found\n");
   }
   else
   {
      emitSolution(&Population[solution]);
   }

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
   while (x == y);

   temp = member->solution[x];
   member->solution[x] = member->solution[y];
   member->solution[y] = temp;
}

void emitSolution(Member_type* member)
{
   char board[MAX_LENGTH][MAX_LENGTH];
   int x, y;

   memset((void*)board, 0, sizeof(char) * MAX_LENGTH * MAX_LENGTH);

   for (x = 0; x < MAX_LENGTH; x++)
   {
      board[x][member->solution[x] - 1] = 'Q';
   }

   printf("board:\n");

   for (y = 0; y < MAX_LENGTH; y++)
   {
      for (x = 0; x < MAX_LENGTH; x++)
      {
         printf(board[x][y] == 'Q' ? "Q " : ". ");
      }

      printf("\n");
   }

   printf("\n\n");
}

float computeEnergy(Member_type* member)
{
   int i, j, x, y, tempX, tempY;
   char board[MAX_LENGTH][MAX_LENGTH];
   int conflicts;
   const int dx[DIAG_CHECK_COUNT] = {-1, 1, -1, 1};
   const int dy[DIAG_CHECK_COUNT] = {-1, 1, 1, -1};

   memset((void*)board, 0, sizeof(char) * MAX_LENGTH * MAX_LENGTH);

   for (i = 0; i < MAX_LENGTH; i++)
   {
      board[i][member->solution[i] - 1] = 'Q';
   }

   /* Walk through each of the Queens, and compute the number of conflicts */
   conflicts = 0;

   for (i = 0; i < MAX_LENGTH; i++)
   {
      x = i;
      y = member->solution[i] - 1;

      /*
       * NOTE: Based upon encoding, horizontal and vertical conflicts
       * will never occur!!!
       */

      /* Check diagonals */
      for (j = 0; j < DIAG_CHECK_COUNT; j++)
      {
         tempX = x;
         tempY = y;

         while ((_Bool)1)
         {
            tempX += dx[j];
            tempY += dy[j];

            if (tempX < 0 || tempX >= MAX_LENGTH || tempY < 0 || tempY >= MAX_LENGTH)
            {
               break;
            }

            if (board[tempX][tempY] == 'Q')
            {
               conflicts++;
            }
         }
      }
   }

   return (float)conflicts;
}

int simulateAnnealing(const float curTemp)
{
   int memberIndex, i;
   Member_type tempMember;
   float energy;
   int useNew;
   int solution = -1;

   for (memberIndex = 0; memberIndex < MAX_MEMBERS; memberIndex++)
   {
      for (i = 0; i < MAX_LENGTH; i++)
      {
         tempMember.solution[i] = Population[memberIndex].solution[i];
      }

      tweakSolution(&tempMember);
      energy = computeEnergy(&tempMember);
      useNew = 0;

      if (energy < Population[memberIndex].energy)
      {
         useNew = 1;
      }
      else
      {
         const float test = GET_S_RAND();
         const float delta = energy - Population[memberIndex].energy;

         if (exp(-delta / curTemp) > test)
         {
            useNew = 1;
         }
      }

      if (useNew)
      {
         for (i = 0; i < MAX_LENGTH; i++)
         {
            Population[memberIndex].solution[i] = tempMember.solution[i];
            Population[memberIndex].energy = energy;
         }
      }

      if (Population[memberIndex].energy == 0)
      {
         solution = memberIndex;
      }
   }

   return solution;
}

void computeAllEnergy()
{
   int member;

   for (member = 0; member < MAX_MEMBERS; member++)
   {
      Population[member].energy = computeEnergy(&Population[member]);
   }
}
