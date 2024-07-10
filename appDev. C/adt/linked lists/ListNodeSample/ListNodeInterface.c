#include "ListNodeInterface.h"

/**
 * \brief Insert a new value into the list in sorted order
 * \param sPtr Starting point node
 * \param value Value to be inserted
 * \return True if node value has been inserted, False - otherwise
 */
_Bool insert(ListNodePtr* sPtr, char value)
{
   ListNodePtr newPtr = (ListNodePtr)malloc(sizeof(ListNode));

   if (newPtr != NULL) // is space available
   {
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node doesn't link to another node

      ListNodePtr previousPtr = NULL;
      ListNodePtr currentPtr = *sPtr;

      // loop to find the correct location in the list
      while (currentPtr != NULL && value > currentPtr->data)
      {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      }

      // insert new node at the beginning of the list
      if (previousPtr == NULL)
      {
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      }
      else // insert new node between previousPtr and currentPtr
      {
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      }

      return TRUE;
   }

   return FALSE; // printf("%c not inserted. No memory available.\n", value)
}

/**
 * \brief Delete a list element
 * \param sPtr Node to be unlinked
 * \param value Value to be deleted
 * \return Deleted char or '\0' - if node hasn't been found
 */
char delete(ListNodePtr* sPtr, char value)
{
   // delete the first node if a match is found
   if (value == (*sPtr)->data)
   {
      const ListNodePtr tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      free(tempPtr); // free the de-threaded node

      return value;
   }

   // find the node
   ListNodePtr previousPtr = *sPtr;
   ListNodePtr currentPtr = (*sPtr)->nextPtr;

   // loop to find the correct location in the list
   while (currentPtr != NULL && currentPtr->data != value)
   {
      previousPtr = currentPtr; // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
   }

   // delete node at currentPtr
   if (currentPtr != NULL)
   {
      const ListNodePtr tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      free(tempPtr);

      return value;
   }

   return '\0';
}

/**
* \brief Find out whether sPtr node is empty
* \param sPtr List node pointer
* \return True, if node is empty, False - otherwise
*/
/*inline */
_Bool isEmpty(const ListNodePtr sPtr)
{
   return sPtr == NULL;
}
