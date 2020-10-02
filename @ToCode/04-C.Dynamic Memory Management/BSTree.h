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
