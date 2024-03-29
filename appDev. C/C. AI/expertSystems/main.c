/*
 * Rules-based system main
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "parser.h"
#include "timers.h"
#include "ruleChk.h"

memoryElementType workingMemory[MAX_MEMORY_ELEMENTS];
int memIndex = 0;
ruleType ruleSet[MAX_RULES];
int ruleIndex;
extern timerType timers[MAX_TIMERS];
int endRun = 0, debug;

/**
 * @brief Debug function to emit the set of parsed rules.
 */
static void printStructure(void);

/**
 * @brief Debug function to emit the current set of facts from the
 *  working memory.
 */
static void printWorkingMemory(void);

/**
 * @brief Emit the command-line help.
 */
static void emitHelp(void);

/**
 * @brief Walk through the active rules looking for a rule that can fire.
 */
static void interpret(void);

/**
 * @brief Main function for the forward-chaining rules-based system.
 * @return Exit code
 */
int main(int argc, char *argv[])
{
   int opt, ret;
   char inpfile[80] = {0};
   debug = 0;
   while ((opt = getopt(argc, argv, "hdr:")) != -1)
   {
      switch (opt)
      {
         case 'r':
            strcpy(inpfile, optarg);
            break;

         case 'd':
            debug = 1;
            printf("Debugging enabled\n");
            break;

         case 'h':
            emitHelp();
            break;

         default:
            emitHelp();
            break;
      }
   }

   if (inpfile[0] == 0)
   {
      emitHelp();
   }

   memset((void *) workingMemory, 0, sizeof(workingMemory));
   memset((void *) ruleSet, 0, sizeof(ruleSet));
   memset((void *) timers, 0, sizeof(timers));
   ret = parseFile(inpfile);
   if (ret < 0)
   {
      printf("\nCould not open file, or parse error\n\n");
      exit(0);
   }

   while (1)
   {
      interpret();
      if (debug)
      {
         printWorkingMemory();
      }

      processTimers();
      if (endRun)
      {
         break;
      }

      sleep(1);
   }

   return 0;
}

void printStructure(void)
{
   memoryElementType *ptr;
   int i;

   printf("Parsed %d rules\n", ruleIndex);
   for (i = 0; i < MAX_RULES; i++)
   {
      if (ruleSet[i].active)
      {
         printf("Rule %d :\n", i);
         printf("Antecedents : \n");
         ptr = ruleSet[i].antecedent;
         while (ptr)
         {
            printf("  %s\n", ptr->element);
            ptr = ptr->next;
         }

         printf("Consequents : \n");
         ptr = ruleSet[i].consequent;
         while (ptr)
         {
            printf("  %s\n", ptr->element);
            ptr = ptr->next;
         }

         printf("\n");
      }
   }
}

void printWorkingMemory(void)
{
   int slot;

   printf("\tWorking Memory:\n");
   for (slot = 0; slot < MAX_MEMORY_ELEMENTS; slot++)
   {
      if (workingMemory[slot].active)
      {
         printf("\t\t%s\n", workingMemory[slot].element);
      }
   }

   printf("\n");
}

void emitHelp(void)
{
   printf("\n\trbs -r <rule file> [-hd]\n\n");
   printf("\t\t -r  specify the rules file\n");
   printf("\t\t -d  debug mode\n");
   printf("\t\t -h  this help\n\n");
   exit(0);
}

void interpret(void)
{
   int rule;
   int fired;

   for (rule = 0; rule < MAX_RULES; rule++)
   {
      fired = 0;
      if (ruleSet[rule].active)
      {
         fired = checkRule(rule);

         /* If a rule had some effect on working memory, exit, otherwise test
          * another rule.
          */
         if (fired)
         {
            break;
         }
      }
   }

   if (debug && fired)
   {
      printf("Fired rule %s (%d)\n", ruleSet[rule].ruleName, rule);
   }
}
