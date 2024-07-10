#include "sd.h"

struct FL flight[MAX];  /* array of db structures */

int f_pos = 0;    /* number of entries in flight db */
int find_pos = 0; /* index for searching flight db */

int tos = 0;     /* top of stack */
int stos = 0;    /* top of solution stack */

struct stack bt_stack[MAX]; /* backtrack stack */
struct stack solution[MAX]; /* hold temporary solutions */

/* Initialize the flight database. */
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

/* Put facts into the database. */
void assert_flight(char *from, char *to, int dist)
{
   if (f_pos < MAX)
   {
      strcpy(flight[f_pos].from, from);
      strcpy(flight[f_pos].to, to);
      flight[f_pos].distance = dist;
      flight[f_pos].skip = 0;
      f_pos++;
   }
   else
   { printf("Flight database full.\n"); }
}

/* Find the shortest distance. */
int route(void)
{
   int dist, t;
   static int old_dist = 32000;

   if (!tos)
   { return 0; }  /* all done */
   t = 0;
   dist = 0;
   while (t < tos)
   {
      dist += bt_stack[t].dist;
      t++;
   }

   /* if shorter then make new solution */
   if (dist < old_dist && dist)
   {
      t = 0;
      old_dist = dist;
      stos = 0; /* clear old route from location stack */
      while (t < tos)
      {
         spush(bt_stack[t].from, bt_stack[t].to, bt_stack[t].dist);
         t++;
      }
   }
   return dist;
}

/* If flight between from and to, then return
   the distance of flight; otherwise, return 0. */
int match(char *from, char *to)
{
   register int t;

   for (t = f_pos - 1; t > -1; t--)
   {
      if (!strcmp(flight[t].from, from) &&
          !strcmp(flight[t].to, to))
      {
         return flight[t].distance;
      }
   }

   return 0;  /* not found */
}

/* Given from, find anywhere. */
int find(char *from, char *anywhere)
{
   find_pos = 0;
   while (find_pos < f_pos)
   {
      if (!strcmp(flight[find_pos].from, from) &&
          !flight[find_pos].skip)
      {
         strcpy(anywhere, flight[find_pos].to);
         flight[find_pos].skip = 1;
         return flight[find_pos].distance;
      }
      find_pos++;
   }
   return 0;
}

/* Determine if there is a route between from and to. */
void isflight(char *from, char *to)
{
   int d, dist;
   char anywhere[20];

   if (d = match(from, to))
   {
      push(from, to, d); /* distance */
      return;
   }

   if (dist = find(from, anywhere))
   {

      push(from, to, dist);
      isflight(anywhere, to);
   }
   else if (tos > 0)
   {
      pop(from, to, &dist);
      isflight(from, to);
   }
}

/* Stack Routines */
void push(char *from, char *to, int dist)
{
   if (tos < MAX)
   {
      strcpy(bt_stack[tos].from, from);
      strcpy(bt_stack[tos].to, to);
      bt_stack[tos].dist = dist;
      tos++;
   }
   else
   { printf("Stack full.\n"); }
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
   { printf("Stack underflow.\n"); }
}

/* Solution Stack */
void spush(char *from, char *to, int dist)
{
   if (stos < MAX)
   {
      strcpy(solution[stos].from, from);
      strcpy(solution[stos].to, to);
      solution[stos].dist = dist;
      stos++;
   }
   else
   { printf("Shortest distance stack full.\n"); }
}