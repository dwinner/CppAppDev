#include <stdlib.h>
#include "linked_list.h"
#include "string.h"
#include "stdio.h"

void dlsStore(struct cell *i, struct cell **start, struct cell **last)
{
   struct cell *old, *p;

   if (!*last) /* first element in list */
   {
      i->next = NULL;
      i->prior = NULL;
      *last = i;
      *start = i;
      return;
   }

   p = *start;   /* start at the top of the list */

   old = NULL;
   while (p)
   {
      if (strcmp(p->cell_name, i->cell_name) < 0)
      {
         old = p;
         p = p->next;
      }
      else
      {
         if (p->prior)  /* is a middle element */
         {
            p->prior->next = i;
            i->next = p;
            i->prior = p->prior;
            p->prior = i;
            return;
         }

         i->next = p;  /* new first element */
         i->prior = NULL;
         p->prior = i;
         *start = i;
         return;
      }
   }

   old->next = i;   /* put on the end */
   i->next = NULL;
   i->prior = old;
   *last = i;
}

void deleteCell(char *cell_name, struct cell **start, struct cell **last)
{
   struct cell *info;

   info = findCell(cell_name, *start);
   if (info)
   {
      if (*start == info)
      {
         *start = info->next;
         if (*start)
         {
            (*start)->prior = NULL;
         }
         else
         {
            *last = NULL;
         }
      }
      else
      {
         if (info->prior)
         {
            info->prior->next = info->next;
         }

         if (info != *last)
         {
            info->next->prior = info->prior;
         }
         else
         {
            *last = info->prior;
         }
      }

      free(info);
   }
}

struct cell *findCell(char *cell_name, struct cell *start)
{
   struct cell *info;

   info = start;
   while (info)
   {
      if (!strcmp(cell_name, info->cell_name))
      {
         return info;
      }

      info = info->next;  /* get next cell */
   }

   printf("Cell is not found\n");

   return NULL;   /* not found */
}
