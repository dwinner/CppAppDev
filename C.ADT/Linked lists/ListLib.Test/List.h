/**
 * Header file for a simple list type
 */

#ifndef LIST_H

#define LIST_H

#include <stdbool.h>

/* program specific declarations */

/**
 * \brief Size of array to hold the title
 */
#define TSIZE  45

/**
 * \brief Film structure
 */
struct film
{
   /**
    * \brief Title
    */
   char title[TSIZE];

   /**
    * \brief Rating
    */
   int rating;
};

/* general type definitions */

/**
 * \brief Film structure
 */
typedef struct film Item;

/**
 * \brief List node
 */
typedef struct node
{
   /**
    * \brief Node item
    */
   Item item;

   /**
    * \brief Pointer to next node
    */
   struct node* next;
} Node;

/**
 * \brief List node pointer
 */
typedef Node* List;

/* function prototypes */

/**
 * \brief Initialize a list
 * \details The list is initialized to empty
 * \param pList Points to a list
 */
void initializeList(List* pList);

/**
 * \brief Determine if list is empty
 * \details pList points to an initialized list
 * \param pList points to an initialized list
 * \return True, if list is empty, False - otherwise
 */
bool isEmpty(const List* pList);

/**
 * \brief Determine if list is full
 * \param pList List pointer which points to an initialized list
 * \return True if list is full, False - otherwise
 */
bool isFull(const List* pList);

/**
 * \brief Determine number of items in list
 * \param pList List pointer which points to an initialized list
 * \return Number of items in list
 */
unsigned int getItemCount(const List* pList);

/**
 * \brief Add item to the end of list
 * \param item Item to be added to list
 * \param pList List pointer which points to an initialized list
 * \return If possible, function adds item to the end of list and returns True; False - otherwise
 */
bool addItem(Item item, List* pList);

/**
 * \brief Apply a function to each item in list
 * \param pList List pointer which points to an ititialized list
 * \param pFun Function pointer which points to a function that takes an Item argument
 *             and has no return value
 * \details The function pointed to by pFun is executed once for each item in the list
 */
void traverse(const List* pList, void (*pFun)(Item itemToProcess));

/**
 * \brief Free allocated memory, if any pList points to an initialized list
 * \param pList List pointer
 * \details Any memory allocated for the list is freed and the list is set to empty
 */
void makeEmpty(List* pList);

#endif // LIST_H
