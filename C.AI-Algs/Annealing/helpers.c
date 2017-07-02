#include "helpers.h"
#include "stdlib.h"

void tweakSolution(memberType* member)
{
   int y;

   int x = randInterval(0U, MAX_LENGTH);
   do
   {
      y = randInterval(0U, MAX_LENGTH);
   }
   while (x == y);

   int temp = member->solution[x];
   member->solution[x] = member->solution[y];
   member->solution[y] = temp;
}

void initializeSolution(memberType* member)
{
   int i;

   for (i = 0; i < MAX_LENGTH; ++i)
   {
      member->solution[i] = i;
   }

   for (i = 0; i < MAX_LENGTH; ++i)
   {
      tweakSolution(member);
   }
}

unsigned randInterval(unsigned min, unsigned max)
{
   int r;
   const unsigned int range = 1 + max - min;
   const unsigned int buckets = RAND_MAX / range;
   const unsigned int limit = buckets * range;

   do
   {
      r = rand();
   }
   while (r >= limit);

   return min + r / buckets;
}

void computeEnergy(memberType* member)
{
   int i;
   char board[MAX_LENGTH][MAX_LENGTH];
   const int dx[4] = {-1,1,-1,1};
   const int dy[4] = {-1,1,1,-1};

   for (i = 0; i < MAX_LENGTH; i++)
   {
      board[i][member->solution[i]] = 'Q';
   }

   /* Считает кол-во конфликтов для каждого ферзя */
   int conflicts = 0;

   for (i = 0; i < MAX_LENGTH; i++)
   {
      int x = i;
      int y = member->solution[i];
      /* NOTE: по условию кодировки конфликты по вертикали и горизонтали исключены */
      /* Проверяем диагонали */
      for (int j = 0; j < 4; ++j)
      {
         int tempx = x;
         int tempy = y;

         while (1)
         {
            tempx += dx[j];
            tempy += dy[j];
            if (tempx < 0 || tempx >= MAX_LENGTH || tempy < 0 || tempy >= MAX_LENGTH)
            {
               break;
            }

            if (board[tempx][tempy] == 'Q')
            {
               conflicts++;
            }
         }
      }
   }

   member->energy = (float)conflicts;
}
