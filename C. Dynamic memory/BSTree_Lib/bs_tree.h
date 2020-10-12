/**
 * A generic binary search tree implementation
 */

#ifndef BS_TREE_H
#define BS_TREE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * \brief Definition for compare function
 * \param pKey1 The 1st generic pointer
 * \param pKey2 The 2nd generic pointer
 * \return	1 - if 1st > 2nd; 0 - if 1st = 2nd; -1 - if 1st < 2nd
 */
typedef int CmpFuncT(const void* pKey1, const void* pKey2);

/**
 * \brief Definition for function returns the key by the data
 * \param pData Generic data
 * \return Generic key based on the data
 */
typedef const void* GetKeyFuncT(const void* pData);

/**
 * \brief Binary tree's node
 */
struct node
{
   /**
    * \brief Pointer to the left node
    */
   struct node* left;

   /**
    * \brief Pointer to the right node
    */
   struct node* right;

   /**
    * \brief Size of the data payload
    */
   size_t size;

   /**
    * \brief The data itself
    */
   char data[];
};

/**
 * \brief Binary tree's node
 */
typedef struct node NodeT;

/**
* \brief Poiner to Node pseuvo name
*/
typedef NodeT* NodePtr;

/**
 * \brief Binary search tree
 */
struct b_tree
{
   /**
    * \brief Pointer to the root
    */
   NodeT* p_root;

   /**
    * \brief Comparison function - compares two keys
    */
   CmpFuncT* cmp;

   /**
    * \brief Get key function - converts data into a key value
    */
   GetKeyFuncT* get_key;
};

/**
 * \brief Binary search tree
 */
typedef struct b_tree BstT;

/**
 * \brief Action function
 * \param pData Data to visit
 * \return true, if data has been taken into accout, false - otherwise
 */
typedef bool (ActionFunc)(void* pData);

/**
 * \brief Creates a new binary search tree
 * \param cmp Comparison function
 * \param getKey Key generator by data function
 * \return The new binary search tree - the 1st argument to all the other binary-tree functions
 */
BstT* new_bst(CmpFuncT* cmp, GetKeyFuncT* getKey);

/**
 * \brief Inserts the new leaf at a position that is consistent with the binary tree’s sorting condition.
 * \details Copies a data item to a new leaf node in the tree
 * \param pBst Tree
 * \param pData Data
 * \param size Size of the data
 * \return true if it succeeds in inserting the new data, false - otherwise
 */
bool bst_insert(BstT* pBst, const void* pData, size_t size);

/**
 * \brief Uses the binary search algorithm to find a data item that matches a given key
 * \param pBst Tree
 * \param pKey Key
 * \return A pointer to the data item of the first node that matches the key, or a null pointer if no match was found
 */
const void* bst_search(BstT* pBst, const void* pKey);

/**
 * \brief Searches for a node that matches the specified key, and deletes it if found.
 * \param pBst Tree
 * \param pKey Key to search
 * \return false if it fails to find a matching node to delete, or true if successful.
 */
bool bst_erase(BstT* pBst, const void* pKey);

/**
 * \brief Deletes all the nodes of a tree
 * \param pBst The tree root  
 */
void bst_clear(BstT* pBst);

/**
 * \brief Traverses the tree in direct order
 * \param pBst The tree
 * \param action Traverse action (calls for each node visited)
 * \return The number of times the action was performed successfully
 */
int bst_inorder(BstT* pBst, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in reverse order
 * \param pBst The tree
 * \param action Traverse action (calls for each node visited)
 * \return The number of times the action was performed successfully
 */
int bst_rev_inorder(BstT* pBst, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in pre order
 * \param pBst The tree
 * \param action Traverse action (calls for each node visited)
 * \return The number of times the action was performed successfully
 */
int bst_preorder(BstT* pBst, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in post order
 * \param pBst The tree
 * \param action Traverse action (calls for each node visited)
 * \return The number of times the action was performed successfully
 */
int bst_postorder(BstT* pBst, bool (*action)(void* pData));

#endif // BS_TREE_H
