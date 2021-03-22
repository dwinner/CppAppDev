#pragma once

#include <stdbool.h>

/**
 * \brief Stack node
 */
struct stackNode
{
   /**
    * \brief Stack data item
    */
   int data;

   /**
    * Stack node pointer
    */
   struct stackNode* nextPtr;
};

/**
 * \brief Synonym for struct stackNode
 */
typedef struct stackNode StackNode;

/************************************************************************/
/* Prototypes                                                     */
/************************************************************************/

/**
 * \brief Insert a node at the stack top
 * \param topPtr Pointer to top of the stack
 * \param info Data to push
 * \return true, if push-operation was successfull, false - otherwise
 */
bool push(StackNode** topPtr, int info);

/**
 * \brief Remove a node from the top of the stack
 * \param topPtr Pointer to the top of the stack
 * \return Poped element
 */
int pop(StackNode** topPtr);

/**
 * \brief Check whether the stack is empty
 * \param topPtr The top of the stack
 * \return true, if stack is empty, false - otherwise
 */
bool isEmpty(StackNode* topPtr);

/**
 * \brief Print the stack
 * \param currentPtr Current element
 */
void printStack(StackNode* currentPtr);
