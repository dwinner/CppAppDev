#include "ruleFire.h"

int findEmptyMemSlot(void)
{
   int i;
   for (i = 0; i < MAX_MEMORY_ELEMENTS; i++)
   {
      if (!workingMemory[i].active)
      {
         break;
      }
   }

   return i;
}

void constructElement(char *new, const char *old, const char *arg)
{
   /* Find the second paren */
   old++;
   while (*old != '(')
   {
      old++;
   }

   while ((*old != 0) && (*old != '?'))
   {
      *new++ = *old++;
   }

   /* This was a complete rule (i.e., no ? element) */
   if (*old == 0)
   {
      *(--new) = 0;
      return;
   }
   else
   {
      /* Copy in the arg */
      while (*arg != 0)
      {
         *new++ = *arg++;
      }

      if (*(new - 1) != ')')
      {
         *new++ = ')';
      }

      *new = 0;
   }
}

int performAddCommand(char *mem)
{
   int slot;

   /* Check to ensure that this element isn't already in working memory */
   for (slot = 0; slot < MAX_MEMORY_ELEMENTS; slot++)
   {
      /* Element is already here, return */
      if (workingMemory[slot].active && !strcmp(workingMemory[slot].element, mem))
      {
         return 0;
      }
   }

   /* Add this element to working memory */
   slot = findEmptyMemSlot();
   if (slot < MAX_MEMORY_ELEMENTS)
   {
      workingMemory[slot].active = 1;
      strcpy(workingMemory[slot].element, mem);
   }
   else
   {
      assert(0);
   }

   return 1;
}

int performDeleteCommand(char *mem)
{
   int slot;
   int ret = 0;
   char term1[MEMORY_ELEMENT_SIZE + 1];
   char term2[MEMORY_ELEMENT_SIZE + 1];
   char wm_term1[MEMORY_ELEMENT_SIZE + 1];
   char wm_term2[MEMORY_ELEMENT_SIZE + 1];

   sscanf(mem, "(%s %s)", term1, term2);

   for (slot = 0; slot < MAX_MEMORY_ELEMENTS; slot++)
   {
      if (workingMemory[slot].active)
      {
         sscanf(workingMemory[slot].element, "(%s %s)", wm_term1, wm_term2);

         if (!strncmp(term1, wm_term1, strlen(term1))
             && !strncmp(term2, wm_term2, strlen(term2)))
         {

            workingMemory[slot].active = 0;
            memset(workingMemory[slot].element, 0, MEMORY_ELEMENT_SIZE);
            ret = 1;
         }
      }
   }

   return ret;
}

int performPrintCommand(const char *element)
{
   char string[MAX_MEMORY_ELEMENTS + 1];
   int i = 0, j = 0;

   /* Find initial '"' */
   while (element[i] != '"')
   {
      i++;
   }

   i++;

   /* Copy until we reach the end */
   while (element[i] != '"')
   {
      string[j++] = element[i++];
   }

   string[j] = 0;
   printf("%s\n", string);

   return 1;
}

int performEnableCommand(char *element)
{
   char *string;
   int timer, expiration;
   string = strstr(element, "timer");
   sscanf(string, "timer %d %d", &timer, &expiration);
   startTimer(timer, expiration);

   return 1;
}

int fireRule(int rule, const char *arg)
{
   int ret;
   memoryElementType *walker = ruleSet[rule].consequent;
   char newCons[MAX_MEMORY_ELEMENTS + 1];

   while (walker)
   {
      if (!strncmp(walker->element, "(add", 4))
      {
         constructElement(newCons, walker->element, arg);
         ret = performAddCommand(newCons);
      }
      else if (!strncmp(walker->element, "(delete", 7))
      {
         constructElement(newCons, walker->element, arg);
         ret = performDeleteCommand(newCons);
      }
      else if (!strncmp(walker->element, "(disable", 8))
      {
         ruleSet[rule].active = 0;
         ret = 1;
      }
      else if (!strncmp(walker->element, "(print", 6))
      {
         ret = performPrintCommand(walker->element);
      }
      else if (!strncmp(walker->element, "(enable", 7))
      {
         ret = performEnableCommand(walker->element);
      }
      else if (!strncmp(walker->element, "(quit", 5))
      {
         extern int endRun;
         endRun = 1;
      }

      walker = walker->next;
   }

   return ret;
}
