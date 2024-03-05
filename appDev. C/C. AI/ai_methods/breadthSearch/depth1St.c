#include "depth1St.h"

FlightDbT flightStorage[MAX_ITEMS];

int flightPosition = 0;

int findPosition = 0;

int topPosition = 0;

/**
 * Backtrack stack
 */
static FlightStackT backTrack[MAX_ITEMS];

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

void assertFlight(char *from, char *to, int aDistance)
{
   if (flightPosition < MAX_ITEMS)
   {
      strcpy(flightStorage[flightPosition].from, from);
      strcpy(flightStorage[flightPosition].to, to);
      flightStorage[flightPosition].distance = aDistance;
      flightStorage[flightPosition].skipped = false;
      flightPosition++;
      return;
   }

   printf("Flight database full.\n");
}

void route(char *to)
{
   int distance;
   int tIdx;

   distance = 0;
   tIdx = 0;
   while (tIdx < topPosition)
   {
      printf("%s to ", backTrack[tIdx].from);
      distance += backTrack[tIdx].distance;
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
      if (!strcmp(flightStorage[tIdx].from, from) && !strcmp(flightStorage[tIdx].to, to))
      {
         return flightStorage[tIdx].distance;
      }
   }

   /* not found */
   return 0;
}

int find(char *from, char *anywhere)
{
   findPosition = 0;
   while (findPosition < flightPosition)
   {
      if (!strcmp(flightStorage[findPosition].from, from) && !flightStorage[findPosition].skipped)
      {
         strcpy(anywhere, flightStorage[findPosition].to);
         flightStorage[findPosition].skipped = true; /* make active */
         return flightStorage[findPosition].distance;
      }

      findPosition++;
   }

   return 0;
}

void isFlight(char *from, char *to)
{
   int dest;
   int dist;
   char anywhere[20];

   dist = find(from, anywhere);
   while (dist)
   {
      /* breadth-first modification */
      dest = match(anywhere, to);
      if (dest)
      {
         push(from, to, dist);
         push(anywhere, to, dest);
         return;
      }

      dist = find(from, anywhere);
   }

   /* try any connection */
   dist = find(from, anywhere);
   if (dist)
   {
      push(from, to, dist);
      isFlight(anywhere, to);
   }
   else if (topPosition > 0)
   {
      pop(from, to, &dist);
      isFlight(from, to);
   }
}

void push(char *from, char *to, int aDistance)
{
   if (topPosition < MAX_ITEMS)
   {
      strcpy(backTrack[topPosition].from, from);
      strcpy(backTrack[topPosition].to, to);
      backTrack[topPosition].distance = aDistance;
      topPosition++;
      return;
   }

   printf("Stack full.\n");
}

void pop(char *from, char *to, int *poDistance)
{
   if (topPosition > 0)
   {
      topPosition--;
      strcpy(from, backTrack[topPosition].from);
      strcpy(to, backTrack[topPosition].to);
      *poDistance = backTrack[topPosition].distance;
      return;
   }

   printf("Stack underflow.\n");
}
