/**
 * Binary search tree - no duplicate items are allowed in this tree
 */

#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#define MAX_ITEMS 10
#define MAX_CHARS 20

/**
 * \brief Redefine item as appropriate
 */
typedef struct item
{
   /**
    * \brief Petname
    */
   char petname[20];
   
   /**
    * \brief Petkind
    */
   char petkind[20];
} Item;

/**
 * \brief Node
 */
typedef struct node
{
   /**
    * \brief Item
    */
   Item item;
   
   /**
    * \brief Left node
    */
   struct node* left;
   
   /**
    * \brief Right node
    */
   struct node* right;
} Node;

/**
 * \brief Tree
 */
typedef struct tree
{
   /**
    * \brief Pointer to root of tree
    */
   Node* root;
   
   /**
    * \brief Number of items in tree
    */
   int size;
} Tree;

/* Function prototypes */

/**
 * \brief Initialize a tree to empty
 * \param treePtr Points to a tree
 */
void initializeTree(Tree* treePtr);

/**
 * \brief Determine if tree is empty
 * \param treePtr Points to a tree
 * \return true if tree is empty, false - otherwise
 */
bool treeIsEmpty(const Tree* treePtr);

/**
 * \brief Determine if tree is full
 * \param treePtr Points to a tree
 * \return true if tree is full, false - otherwise
 */
bool treeIsFull(const Tree* treePtr);

/**
 * \brief Determine number of items in tree
 * \param treePtr Points to a tree
 * \return Number of items in tree
 */
int treeItemCount(const Tree* treePtr);

/**
 * \brief Add an item to a tree
 * \param itemPtr Item to add
 * \param treePtr Pointer to previously initialized tree
 * \return  if possible, function adds item to tree and
 *          returns true; otherwise function returns false
 */
bool addItem(const Item* itemPtr, Tree* treePtr);

/**
 * \brief Find an item in a tree
 * \param itemPtr Item pointer to search
 * \param treePtr Pointer to initialized tree
 * \return true if item is in tree, false - otherwise
 */
bool inTree(const Item* itemPtr, const Tree* treePtr);

/**
 * \brief Delete an item from a tree
 * \param itemPtr Item to be deleted
 * \param treePtr Pointer to an initialized tree
 * \return  if possible, function deletes item from tree and returns true;
 *          otherwise, the function returns false
 */
bool deleteItem(const Item* itemPtr, Tree* treePtr);

/**
 * \brief Apply a function to each item in the tree
 * \param treePtr Points to a tree
 * \param funPtr  Points to a function that takes an Item
 *                argument and has no return value. The function
 *                ponted to by funPtr is executed once for each item in tree
 */
void traverse(const Tree* treePtr, void(*funPtr)(Item item));

/**
 * \brief Delete everything from a tree
 * \param treePtr Pointer to an initialized tree
 */
void deleteAll(Tree* treePtr);

#endif // TREE_H