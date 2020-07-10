//
// Created by Vinevtsev on 8/8/2019.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash_cell.h"

void init(void)
{
   register int i;

   for (i = 0; i < MAX; ++i)
   {
      primary[i].index = -1;
      primary[i].next = NULL;   /* null chain */
      primary[i].val = 0;
   }
}

void store(char *cell_name, int value)
{
   int h, loc;
   struct hashType *p;

   /* produce the hash value */
   loc = *cell_name - 'A';  /* column */
   loc += (atoi(&cell_name[1]) - 1) * 26; /* rows * width + columns */
   h = loc / 10;   /* hash */

   /* Store in the location unless full or
      store there if logical indexes agree - i.e., update. */
   if (primary[h].index == -1 || primary[h].index == loc)
   {
      primary[h].index = loc;
      primary[h].val = value;
      return;
   }

   /* otherwise, create or add to collision list */
   p = (struct hashType *) malloc(sizeof(struct hashType));
   if (!p)
   {
      printf("Out of memory\n");
      return;
   }

   p->index = loc;
   p->val = value;
   slstore(p, &primary[h]);
}

void slstore(struct hashType *i, struct hashType *start)
{
   struct hashType *old, *p;

   old = start;

   /* find end of list */
   while (start)
   {
      old = start;
      start = start->next;
   }

   /* link in new entry */
   old->next = i;
   i->next = NULL;
}

int find(char *cell_name)
{
   int h, loc;
   struct hashType *p;

   /* produce the hash value */
   loc = *cell_name - 'A';  /* column */
   loc += (atoi(&cell_name[1]) - 1) * 26; /* rows * width + column */
   h = loc / 10;

   /* return the value if found */
   if (primary[h].index == loc)
   {
      return primary[h].val;
   }
   else  /* look in collision list */
   {
      p = primary[h].next;
      while (p)
      {
         if (p->index == loc)
         {
            return p->val;
         }

         p = p->next;
      }

      printf("Not in array.\n");

      return -1;
   }
}
