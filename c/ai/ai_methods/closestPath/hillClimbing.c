#include "hillClimbing.h"

/**
 * array of db structures
 */
struct Flight flight[MAX];

/**
 * number of entries in flight db
 */
int flightPosition = 0;

/**
 * index for searching flight db
 */
int findPosition = 0;

/**
 * top of Stack
 */
int stackTop = 0;

/**
 * backtrack Stack
 */
struct Stack backTrackSt[MAX];

void setup(void)
{
   assertFlight("New York", "Chicago", 1000);
   assertFlight("Chicago", "Denver", 1000);
   assertFlight("New York", "Toronto", 800);
   assertFlight("New York", "Denver", 1900);
   assertFlight("Toronto", "Calgary", 1500);
   assertFlight("Toronto", "Los Angeles", 1800);
   assertFlight("Toronto", "Chicago", 500);
   assertFlight("Denver", "Urbana", 1000);
   assertFlight("Denver", "Houston", 1500);
   assertFlight("Houston", "Los Angeles", 1500);
   assertFlight("Denver", "Los Angeles", 1000);
}

void assertFlight(char *from, char *to, int distance)
{
   if (flightPosition < MAX)
   {
      strcpy(flight[flightPosition].from, from);
      strcpy(flight[flightPosition].to, to);
      flight[flightPosition].distance = distance;
      flight[flightPosition].skip = false;
      flightPosition++;
   }
   else
   {
      printf("Flight database full.\n");
   }
}

void route(char *to)
{
   int distance;
   int tIdx;

   distance = 0;
   tIdx = 0;
   while (tIdx < stackTop)
   {
      printf("%s to ", backTrackSt[tIdx].from);
      distance += backTrackSt[tIdx].dist;
      tIdx++;
   }

   printf("%s\n", to);
   printf("Distance is %d.\n", distance);
}

int match(char *from, char *to)
{
   register int tIdx;

   for (tIdx = flightPosition - 1; tIdx > -1; tIdx--)
   {
      struct Flight curFlight = flight[tIdx];
      if (!strcmp(curFlight.from, from) && !strcmp(curFlight.to, to))
      {
         return curFlight.distance;
      }
   }

   return 0; /* not found */
}

int find(char *from, char *anywhere)
{
   int pos;
   int dist;

   pos = dist = 0;
   findPosition = 0;

   while (findPosition < flightPosition)
   {
      struct Flight curFlight = flight[findPosition];
      if (!strcmp(curFlight.from, from) && !curFlight.skip && curFlight.distance < dist)
      {
         pos = findPosition;
         dist = curFlight.distance;
      }

      findPosition++;
   }

   if (pos)
   {
      strcpy(anywhere, flight[pos].to);
      flight[pos].skip = true;
      return flight[pos].distance;
   }

   return 0;
}

void isFlight(char *from, char *to)
{
   int mDist;
   int fDist;
   char anywhere[20];

   mDist = match(from, to);
   if (mDist)
   {
      /* is goal */
      push(from, to, mDist);
      return;
   }

   /* find any connection */
   fDist = find(from, anywhere);
   if (fDist)
   {
      push(from, to, fDist);
      isFlight(anywhere, to);
   }
   else if (stackTop > 0)
   {
      pop(from, to, &fDist);
      isFlight(from, to);
   }
}

void push(char *from, char *to, int distance)
{
   if (stackTop < MAX)
   {
      strcpy(backTrackSt[stackTop].from, from);
      strcpy(backTrackSt[stackTop].to, to);
      backTrackSt[stackTop].dist = distance;
      stackTop++;
   }
   else
   {
      printf("Stack full.\n");
   }
}

void pop(char *from, char *to, int *poDistance)
{
   if (stackTop > 0)
   {
      stackTop--;
      strcpy(from, backTrackSt[stackTop].from);
      strcpy(to, backTrackSt[stackTop].to);
      *poDistance = backTrackSt[stackTop].dist;
   }
   else
   {
      printf("Stack underflow.\n");
   }
}