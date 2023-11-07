#include "depth1St.h"

FlightT flightStorage[MAX_ITEMS];

int f_pos = 0;

int find_pos = 0;

int tos = 0;

/**
 * Backtrack stack
 */
static StackT bt_stack[MAX_ITEMS];

void setup(void)
{
   assert_flight("New York", "Chicago", 1000);
   assert_flight("Chicago", "Denver", 1000);
   assert_flight("New York", "Toronto", 800);
   assert_flight("New York", "Denver", 1900);
   assert_flight("Toronto", "Calgary", 1500);
   assert_flight("Toronto", "Los Angeles", 1800);
   assert_flight("Toronto", "Chicago", 500);
   assert_flight("Denver", "Urbana", 1000);
   assert_flight("Denver", "Houston", 1500);
   assert_flight("Houston", "Los Angeles", 1500);
   assert_flight("Denver", "Los Angeles", 1000);
}

void assert_flight(char *from, char *to, int dist)
{
   if (f_pos < MAX_ITEMS)
   {
      strcpy(flightStorage[f_pos].from, from);
      strcpy(flightStorage[f_pos].to, to);
      flightStorage[f_pos].distance = dist;
      flightStorage[f_pos].skip = 0;
      f_pos++;
   }
   else
   {
      printf("Flight database full.\n");
   }
}

void route(char *to)
{
   int dist, t;

   dist = 0;
   t = 0;
   while (t < tos)
   {
      printf("%s to ", bt_stack[t].from);
      dist += bt_stack[t].dist;
      t++;
   }

   printf("%s\n", to);
   printf("Distance is %d.\n", dist);
}

int match(char *from, char *to)
{
   register int t;

   for (t = f_pos - 1; t > -1; t--)
   {
      if (!strcmp(flightStorage[t].from, from)
          && !strcmp(flightStorage[t].to, to))
      {
         return flightStorage[t].distance;
      }
   }

   /* not found */
   return 0;
}

int find(char *from, char *anywhere)
{
   find_pos = 0;
   while (find_pos < f_pos)
   {
      if (!strcmp(flightStorage[find_pos].from, from)
          && !flightStorage[find_pos].skip)
      {
         strcpy(anywhere, flightStorage[find_pos].to);
         flightStorage[find_pos].skip = 1; /* make active */
         return flightStorage[find_pos].distance;
      }

      find_pos++;
   }

   return 0;
}

void isFlight(char *from, char *to)
{
   int d, dist;
   char anywhere[20];

   /* see if at destination */
   if (d = match(from, to))
   {
      push(from, to, d);
      return;
   }

   /* try another connection */
   if (dist = find(from, anywhere))
   {
      push(from, to, dist);
      isFlight(anywhere, to);
   }
   else if (tos > 0)
   {
      /* backtrack */
      pop(from, to, &dist);
      isFlight(from, to);
   }
}

void push(char *from, char *to, int dist)
{
   if (tos < MAX_ITEMS)
   {
      strcpy(bt_stack[tos].from, from);
      strcpy(bt_stack[tos].to, to);
      bt_stack[tos].dist = dist;
      tos++;
   }
   else
   {
      printf("Stack full.\n");
   }
}

void pop(char *from, char *to, int *dist)
{
   if (tos > 0)
   {
      tos--;
      strcpy(from, bt_stack[tos].from);
      strcpy(to, bt_stack[tos].to);
      *dist = bt_stack[tos].dist;
   }
   else
   {
      printf("Stack underflow.\n");
   }
}
