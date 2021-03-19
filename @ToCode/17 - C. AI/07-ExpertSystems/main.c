/*
 *  Rules-based system main 
 *
 *  ./software/ch8/main.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common.h"

memoryElementType workingMemory[MAX_MEMORY_ELEMENTS];
int memIndex = 0;

ruleType ruleSet[MAX_RULES];
int ruleIndex;

extern timerType timers[MAX_TIMERS];

int endRun = 0, debug;

/*
 *  printStructure()
 *
 *  Debug function to emit the set of parsed rules.
 *
 */

void printStructure( void )
{
  memoryElementType *ptr;
  int i;

  printf("Parsed %d rules\n", ruleIndex);

  for (i = 0 ; i < MAX_RULES ; i++) {

    if (ruleSet[i].active) {

      printf("Rule %d :\n", i);
      printf("Antecedents : \n");
      ptr = ruleSet[i].antecedent;
      while (ptr) {
        printf("  %s\n", ptr->element);
        ptr = ptr->next;
      }
      printf("Consequents : \n");
      ptr = ruleSet[i].consequent;
      while (ptr) {
        printf("  %s\n", ptr->element);
        ptr = ptr->next;
      }
      printf("\n");

    }
  }
}


/*
 *  printWorkingMemory()
 *
 *  Debug function to emit the current set of facts from the 
 *  working memory.
 *
 */

void printWorkingMemory( void )
{
  int slot;

  printf("\tWorking Memory:\n");

  for (slot = 0 ; slot < MAX_MEMORY_ELEMENTS ; slot++) {

    if (workingMemory[slot].active) {

      printf("\t\t%s\n", workingMemory[slot].element);

    }

  }

  printf("\n");
}


/*
 *  emitHelp()
 *
 *  Emit the command-line help.
 *
 */

void emitHelp( void )
{
  printf("\n\trbs -r <rule file> [-hd]\n\n");
  printf("\t\t -r  specify the rules file\n");
  printf("\t\t -d  debug mode\n");
  printf("\t\t -h  this help\n\n");
  exit(0);
}


/*
 *  main()
 *
 *  Main function for the forward-chaining rules-based system.
 *
 */

int main( int argc, char *argv[] )
{
  int opt, ret;
  char inpfile[80]={0};

  extern void processTimers( void );
  extern int parseFile( char * );
  extern void interpret( void );

  debug = 0;

  while ((opt = getopt(argc, argv, "hdr:")) != -1) {

    switch( opt ) {

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

    }

  }

  if (inpfile[0] == 0) emitHelp();

  bzero( (void *)workingMemory, sizeof(workingMemory) );
  bzero( (void *)ruleSet, sizeof(ruleSet) );
  bzero( (void *)timers, sizeof(timers) );

  ret = parseFile( inpfile );

  if (ret < 0) {
    printf("\nCould not open file, or parse error\n\n");
    exit(0);
  }

//  printStructure();

  while (1) {

    interpret();

    if (debug) {
      printWorkingMemory();
    }

    processTimers();

    if (endRun) break;

    sleep(1);

  }

  return 0;
}
