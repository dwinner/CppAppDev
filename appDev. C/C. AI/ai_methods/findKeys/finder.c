#include "finder.h"

/**
 * Array of db structures
 */
KeyTypeT keys[MAX];

/**
 * Number of rooms in house
 */
int roomsCount = 0;

/**
 * Index for searching keys db
 */
int findPos = 0;

/**
 * Top of stack
 */
int stackTop = 0;

/**
 * Backtrack stack
 */
StackT bt_stack[MAX];

void setup(void)
{
   assertKeys("front_door", "lr");
   assertKeys("lr", "bath");
   assertKeys("lr", "hall");
   assertKeys("hall", "bd1");
   assertKeys("hall", "bd2");
   assertKeys("hall", "mb");
   assertKeys("lr", "kitchen");
   assertKeys("kitchen", "keys");
}

void assertKeys(char *from, char *to)
{
   if (roomsCount < MAX)
   {
      strcpy(keys[roomsCount].from, from);
      strcpy(keys[roomsCount].to, to);
      keys[roomsCount].skipped = false;
      roomsCount++;
   }
   else
   {
      printf("Keys database full.\n");
   }
}

void route(void)
{
   int tIdx;

   tIdx = 0;
   while (tIdx < stackTop)
   {
      printf("'%s'", bt_stack[tIdx].from);
      tIdx++;
      if (tIdx < stackTop)
      {
         printf(" To ");
      }
   }

   printf("\n");
}

bool match(char *from, char *to)
{
   register int tIdx;

   for (tIdx = roomsCount - 1; tIdx > -1; tIdx--)
   {
      if (!strcmp(keys[tIdx].from, from) && !strcmp(keys[tIdx].to, to))
      {
         return true;
      }
   }

   return false;
}

bool find(char *from, char *anywhere)
{
   findPos = 0;

   while (findPos < roomsCount)
   {
      if (!strcmp(keys[findPos].from, from) && !keys[findPos].skipped)
      {
         strcpy(anywhere, keys[findPos].to);
         keys[findPos].skipped = true;
         return true;
      }

      findPos++;
   }

   return false;
}

void isKeys(char *from, char *to)
{
   char anywhere[20];

   if (match(from, to))
   {
      push(from, to); /* distance */
      return;
   }

   if (find(from, anywhere))
   {
      push(from, to);
      isKeys(anywhere, to);
   }
   else if (stackTop > 0)
   {
      pop(from, to);
      isKeys(from, to);
   }
}

void push(char *from, char *to)
{
   if (stackTop < MAX)
   {
      strcpy(bt_stack[stackTop].from, from);
      strcpy(bt_stack[stackTop].to, to);
      stackTop++;
   }
   else
   {
      printf("Stack full.\n");
   }
}

void pop(char *from, char *to)
{
   if (stackTop > 0)
   {
      stackTop--;
      strcpy(from, bt_stack[stackTop].from);
      strcpy(to, bt_stack[stackTop].to);
   }
   else
   {
      printf("Stack underflow.\n");
   }
}
