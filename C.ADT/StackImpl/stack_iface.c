#include "stack_iface.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool push(StackNode** topPtr, const int info)
{
   StackNode* newPtr = (StackNode*)malloc(sizeof(StackNode));

   // insert the node at the top of the stack
   if (newPtr != NULL)
   {
      newPtr->data = info;
      newPtr->nextPtr = *topPtr;
      *topPtr = newPtr;

      return true;
   }

   return false;
}

int pop(StackNode** topPtr)
{
   StackNode* tempPtr = *topPtr;
   const int popValue = (*topPtr)->data;
   *topPtr = (*topPtr)->nextPtr;
   free(tempPtr);
   return popValue;
}

bool isEmpty(StackNode* topPtr)
{
   return topPtr == NULL;
}

void printStack(StackNode* currentPtr)
{
   if (currentPtr == NULL)
   {
      puts("The stack is empty.\n");
   }
   else
   {
      puts("The stack is:");

      while (currentPtr != NULL)
      {
         printf("%d --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;
      }

      puts("NULL\n");
   }
}
