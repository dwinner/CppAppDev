/**
* List node interface declarations
*/
#ifndef LISTNODEINTERFACE_H
#define LISTNODEINTERFACE_H

#include <stdlib.h>

#define TRUE   ((_Bool)1)
#define FALSE  ((_Bool)0)

/**
 * \brief Self-referential structure
 */
struct listNode
{
   /**
    * \brief Each listNode contains a character
    */
   char data;


   /**
    * \brief Poiner to next node
    */
   struct listNode* nextPtr;
};

/**
 * \brief Synonym for struct listNode
 */
typedef struct listNode ListNode;

/**
 * \brief Synonym for ListNode*
 */
typedef ListNode* ListNodePtr;

/******************************** Prototypes ********************************/

/**
 * \brief Insert a new value into the list in sorted order
 * \param sPtr Starting point node
 * \param value Value to be inserted
 * \return True if node value has been inserted, False - otherwise
 */
_Bool insert(ListNodePtr* sPtr, char value);

/**
 * \brief Delete a list element
 * \param sPtr Node to be unlinked
 * \param value Value to be deleted
 * \return Deleted char or '\0' - if node hasn't been found
 */
char delete(ListNodePtr* sPtr, char value);

/**
 * \brief Find out whether sPtr node is empty
 * \param sPtr List node pointer
 * \return True, if node is empty, False - otherwise
 */
/*inline */
_Bool isEmpty(ListNodePtr sPtr);

/*****************************************************************************/

#endif // LISTNODEINTERFACE_H
