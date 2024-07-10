#include <stdio.h>
#include <string.h>
#include <math.h>
#include "emsapop.h"

#include <stdbool.h>
#include <stdlib.h>

Member_type Population[MAX_MEMBERS];

void InitializePopulation()
{
   int index;
   for (int member = 0; member < MAX_MEMBERS; member++)
   {
      /* Initial setup of the solution */
      for (index = 0; index < MAX_LENGTH; index++)
      {
         Population[member].solution[index] = (char)(index + 1);
      }

      /* Randomly perturb the solution */
      for (index = 0; index < MAX_LENGTH; index++)
      {
         const int x = GET_RAND(MAX_LENGTH);
         const int temp = (unsigned char)Population[member].solution[index];
         Population[member].solution[index] = Population[member].solution[x];
         Population[member].solution[x] = (char)temp;
      }
   }
}

void TweakSolution(Member_type* member)
{
   int y;
   const int x = GET_RAND(MAX_LENGTH);

   do
   {
      y = GET_RAND(MAX_LENGTH);
   }
   while (x == y);

   const int temp = (unsigned char)member->solution[x];
   member->solution[x] = member->solution[y];
   member->solution[y] = (char)temp;
}

void EmitSolution(const Member_type* member)
{
   char board[MAX_LENGTH][MAX_LENGTH];
   int x;

   memset(board, 0, sizeof(char) * MAX_LENGTH * MAX_LENGTH);
   for (x = 0; x < MAX_LENGTH; x++)
   {
      board[x][member->solution[x] - 1] = 'Q';
   }

   printf("board:\n");

   for (int y = 0; y < MAX_LENGTH; y++)
   {
      for (x = 0; x < MAX_LENGTH; x++)
      {
         printf(board[x][y] == 'Q' ? "Q " : ". ");
      }

      printf("\n");
   }

   printf("\n\n");
}

float ComputeEnergy(const Member_type* member)
{
   int i;
   char board[MAX_LENGTH][MAX_LENGTH];
   const int dx[DIAG_CHECK_COUNT] = {-1, 1, -1, 1};
   const int dy[DIAG_CHECK_COUNT] = {-1, 1, 1, -1};

   memset(board, 0, sizeof(char) * MAX_LENGTH * MAX_LENGTH);
   for (i = 0; i < MAX_LENGTH; i++)
   {
      board[i][member->solution[i] - 1] = 'Q';
   }

   /* Walk through each of the Queens, and compute the number of conflicts */
   int conflicts = 0;
   for (i = 0; i < MAX_LENGTH; i++)
   {
      const int x = i;
      const int y = member->solution[i] - 1;

      /*
       * Based upon encoding, horizontal and vertical conflicts
       * will never occur!!!
       */

      /* Check diagonals */
      for (int j = 0; j < DIAG_CHECK_COUNT; j++)
      {
         int tempX = x;
         int tempY = y;

         while (true)
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

int SimulateAnnealing(const float curTemp)
{
   int i;
   Member_type tempMember;
   int solution = -1;

   for (int memberIndex = 0; memberIndex < MAX_MEMBERS; memberIndex++)
   {
      for (i = 0; i < MAX_LENGTH; i++)
      {
         tempMember.solution[i] = Population[memberIndex].solution[i];
      }

      TweakSolution(&tempMember);
      const float energy = ComputeEnergy(&tempMember);
      bool useNew = false;
      if (energy < Population[memberIndex].energy)
      {
         useNew = true;
      }
      else
      {
         const float test = GET_S_RAND();
         const float delta = energy - Population[memberIndex].energy;
         if (expf(-delta / curTemp) > test)
         {
            useNew = true;
         }
      }

      if (useNew == true)
      {
         for (i = 0; i < MAX_LENGTH; i++)
         {
            Population[memberIndex].solution[i] = tempMember.solution[i];
            Population[memberIndex].energy = energy;
         }
      }

      const double epsilon = 1E-6;
      if (fabs((double)Population[memberIndex].energy - 0) < epsilon == true)
      {
         solution = memberIndex;
      }
   }

   return solution;
}

void ComputeAllEnergy()
{
   for (int member = 0; member < MAX_MEMBERS; member++)
   {
      Population[member].energy = ComputeEnergy(&Population[member]);
   }
}
