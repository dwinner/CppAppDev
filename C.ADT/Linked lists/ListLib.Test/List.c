/**
 * Functions supporting list operations
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/* local function prototypes */

static void copyToNode(Item item, Node* pNode);

/* Interface functions */

void initializeList(List* pList)
{
   *pList = NULL;
}

bool isEmpty(const List* pList)
{
   return *pList == NULL ? true : false;
}

bool isFull(const List* pList)
{
   Node* pt = (Node*)malloc(sizeof(Node));
   free(pt);
   return pt == NULL;
}

unsigned getItemCount(const List* pList)
{
   unsigned int count = 0;
   Node* pNode = *pList; /* set to start of list */

   while (pNode != NULL)
   {
      ++count;
      pNode = pNode->next; /* set to next node */
   }

   return count;
}

bool addItem(Item item, List* pList)
{
   Node* pNew;
   Node* scan = *pList;

   pNew = (Node*)malloc(sizeof(Node));
   if (pNew == NULL)
   {
      return false; /* quit function on failure */
   }

   copyToNode(item, pNew);
   pNew->next = NULL;
   if (scan == NULL) /* empty list, so place */
   {
      *pList = pNew; /* pNew at head of list */
   }
   else
   {
      while (scan->next != NULL)
      {
         scan = scan->next; /* find end of list */
      }

      scan->next = pNew;
   }

   return true;
}

void traverse(const List* pList, void (* pFun)(Item itemToProcess))
{
   Node* pNode = *pList; /* set to start of list */

   while (pNode != NULL)
   {
      (*pFun)(pNode->item); /* apply function to item */
      pNode = pNode->next; /* advance to next item */
   }
}

void makeEmpty(List* pList)
{
   Node* pSave;

   while (*pList != NULL)
   {
      pSave = (*pList)->next; /* save address of the next node */
      free(*pList); /* free current node */
      *pList = pSave;
   }
}

/**
 * \brief Copies an item into a node
 * \param item Item to copy
 * \param pNode pointer to node where the item will be copied
 */
static void copyToNode(Item item, Node* pNode)
{
   pNode->item = item; /* structure copy */
}
