// A binary search tree (BST)
// BSTree.h

#include <stdbool.h>

typedef int CmpFunc_t( const void *pKey1, const void *pKey2);
typedef const void *GetKeyFunc_t( const void *pData);

typedef struct { struct Node  *pRoot;       // Pointer to the root.
                 CmpFunc_t    *cmp;         // Compares two keys.
                 GetKeyFunc_t *getKey;      // Converts data into a key value
               } BST_t;

BST_t *     newBST( CmpFunc_t *cmp, GetKeyFunc_t *getKey);
_Bool       BST_insert( BST_t *pBST, const void *pData, size_t size);
const void *BST_search( BST_t *pBST, const void *pKey);
_Bool       BST_erase( BST_t *pBST, const void *pKey);
void        BST_clear( BST_t *pBST);

// Each of the folowing functions traverses the tree in a certain order, and 
// calls the function referenced by action for each node. If the action modifies 
// the node's data, then at least the key value must remain unchanged to preserve 
// the tree's sorting order.
int BST_inorder( BST_t *pBST, _Bool (*action)(void *pData));
int BST_rev_inorder( BST_t *pBST, _Bool (*action)(void *pData));
int BST_preorder( BST_t *pBST, _Bool (*action)(void *pData));
int BST_postorder( BST_t *pBST, _Bool (*action)(void *pData));
