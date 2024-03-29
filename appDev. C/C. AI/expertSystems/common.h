//
// Rules based system types and symbolics
//

#ifndef EXPERTSYSTEMS_COMMON_H
#define EXPERTSYSTEMS_COMMON_H

#define MEMORY_ELEMENT_SIZE   80

typedef struct memoryElementStruct *memPtr;

typedef struct memoryElementStruct
{
   int active;
   char element[MEMORY_ELEMENT_SIZE + 1];
   struct memoryElementStruct *next;
} memoryElementType;

#define MAX_MEMORY_ELEMENTS   40
#define MAX_RULES      40

typedef struct
{
   int active;
   char ruleName[MEMORY_ELEMENT_SIZE + 1];
   memoryElementType *antecedent;
   memoryElementType *consequent;
} ruleType;


#define MAX_TIMERS      10

typedef struct
{
   int active;
   int expiration;
} timerType;

#endif //EXPERTSYSTEMS_COMMON_H
