#include "removal.h"

/**
 * Flight DB
 */
FlightItemT flightDb[MAX];

/**
 * Number of entries in Flight DB
 */
int findPos = 0;

/**
 * Index for searching flightDb
 */
int findIdx = 0;

/**
 * Top of stack
 */
int stackTop = 0;

/**
 * Backtrack stack
 */
StackT backTrack[MAX];

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
   if (findPos < MAX)
   {
      strcpy(flightDb[findPos].from, from);
      strcpy(flightDb[findPos].to, to);
      flightDb[findPos].distance = distance;
      flightDb[findPos].skip = 0;
      findPos++;
   }
   else
   {
      printf("Flight database full.\n");
   }
}

void clearMarkers()
{
   int tIdx;
   for (tIdx = 0; tIdx < findPos; ++tIdx)
   {
      flightDb[tIdx].skip = false;
   }
}

void retract(char *from, char *to)
{
   int tIdx;
   for (tIdx = 0; tIdx < findPos; tIdx++)
   {
      if (!strcmp(flightDb[tIdx].from, from) && !strcmp(flightDb[tIdx].to, to))
      {
         strcpy(flightDb[tIdx].from, "");
         return;
      }
   }
}

void route(char *to)
{
   int distance, tIdx;

   distance = 0;
   tIdx = 0;
   while (tIdx < stackTop)
   {
      printf("%s to ", backTrack[tIdx].from);
      distance += backTrack[tIdx].distance;
      tIdx++;
   }

   printf("%s\n", to);
   printf("Distance is %d.\n", distance);
}

int find(char *from, char *anywhere)
{
   findIdx = 0;
   while (findIdx < findPos)
   {
      if (!strcmp(flightDb[findIdx].from, from) && !flightDb[findIdx].skip)
      {
         strcpy(anywhere, flightDb[findIdx].to);
         flightDb[findIdx].skip = true;
         return flightDb[findIdx].distance;
      }

      findIdx++;
   }

   return 0;
}

int match(char *from, char *to)
{
   register int tIdx;
   for (tIdx = findPos - 1; tIdx > -1; tIdx--)
   {
      if (!strcmp(flightDb[tIdx].from, from) && !strcmp(flightDb[tIdx].to, to))
      {
         return flightDb[tIdx].distance;
      }
   }

   return 0; /* not found */
}

void isFlight(char *from, char *to)
{
   int dest, dist;
   char anywhere[20];

   dest = match(from, to);
   if (dest)
   {
      push(from, to, dest); /* distance */
      return;
   }

   dist = find(from, anywhere);
   if (dist)
   {
      push(from, to, dist);
      isFlight(anywhere, to);
   }
   else if (stackTop > 0)
   {
      pop(from, to, &dist);
      isFlight(from, to);
   }
}

void push(char *from, char *to, int distance)
{
   if (stackTop < MAX)
   {
      strcpy(backTrack[stackTop].from, from);
      strcpy(backTrack[stackTop].to, to);
      backTrack[stackTop].distance = distance;
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
      strcpy(from, backTrack[stackTop].from);
      strcpy(to, backTrack[stackTop].to);
      *poDistance = backTrack[stackTop].distance;
   }
   else
   {
      printf("Stack underflow.\n");
   }
}
