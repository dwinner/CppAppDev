static Node_t *detachMin( Node_t **ppNode )
{
    Node_t *pNode = *ppNode;                  // A pointer to the current node.
    if ( pNode == NULL )
      return NULL;                            // pNode is an empty subtree.
    else if ( pNode->left != NULL )
      return detachMin( &(pNode->left) );     // The minimum is in the left subtree.
    else
    {                                         // pNode points to the minimum node.
      *ppNode = pNode->right;                 // Attach the right child to the parent.
      return pNode;
    }
}

_Bool BST_erase(BST_t *pBST, const void *pKey)
{
    if( pBST == NULL || pKey == NULL) 
      return false;
    return erase( pBST, &(pBST->pRoot), pKey);      // Start at the root of the tree.
}

// The recursive helper function erase():
static _Bool erase( BST_t *pBST, Node_t **ppNode, const void *pKey )
{
   Node_t *pNode = *ppNode;            // Pointer to the current node.
   if ( pNode == NULL )
      return false;                    // No match found.
                                       // Compare data:
   int cmp_res = pBST->cmp( pKey, pBST->getKey(pNode->data) );

   if ( cmp_res < 0 )                            // Continue the search
     return erase( pBST, &(pNode->left), pKey);  // in the left subtree,
   else if ( cmp_res > 0 )
     return erase( pBST, &(pNode->right), pKey); // or in the right subtree.
   else
   {                                   // Found the node to be deleted.
     if ( pNode->left == NULL )        // If no more than one child,
       *ppNode = pNode->right;         // attach the child to the parent.
     else if ( pNode->right == NULL )
       *ppNode = pNode->left;
     else                              // Two children: replace the node with
     {                                 // the minimum from the right subtree.
       Node_t *pMin = detachMin( &(pNode->right) );
       *ppNode = pMin;            // Graft it onto the deleted node's parent.
       pMin->left = pNode->left;       // Graft the deleted node's children.
       pMin->right = pNode->right;
     }
     free( pNode );                    // Release the deleted node's storage.
     return true;
   }
}

// -------------------------------------------------------------------------------
// The BST_clear() function deletes all the nodes of a tree.

static void clear( Node_t *pNode );
void BST_clear( BST_t *pBST )
{
    if ( pBST != NULL)
    {
       clear( pBST->pRoot );
       pBST->pRoot = NULL;
    }
}

// The recursive helper function clear():
static void clear( Node_t *pNode )
{
    if ( pNode != NULL )
    {
       clear( pNode->left );
       clear( pNode->right );
       free( pNode );
    }
}

// -------------------------------------------------------------------------------
// Each of the following traversal functions takes as its second argument a pointer
// to an “action” function that it calls for each node visited. 
// The return value is the number of times the action was performed successfully.

static int inorder( Node_t *pNode, _Bool (*action)(void *pData));

int BST_inorder( BST_t *pBST, _Bool (*action)(void *pData))
{
    if( pBST == NULL || action == NULL)
        return 0;
    else
        return inorder( pBST->pRoot, action);
}

// The recursive helper function inorder():
static int inorder( Node_t *pNode, _Bool (*action)(void *pData))
{
    int count = 0;
    if( pNode == NULL)
        return 0;

    count = inorder( pNode->left, action );        // L: Traverse the left
                                                   // subtree.
    if ( action( pNode->data ))                    // N: Visit the current
      ++count;                                     // node itself.
    count += inorder( pNode->right, action );      // R: Traverse the right
                                                   // subtree.
    return count;
}

// -------------------------------------------------------------------------------
static int rev_inorder( Node_t *pNode, _Bool (*action)(void *pData));

int BST_rev_inorder( BST_t *pBST, _Bool (*action)(void *pData))
{
    if( pBST == NULL || action == NULL)
        return 0;
    else
        return rev_inorder( pBST->pRoot, action);
}

// The recursive helper function rev_inorder():
static int rev_inorder( Node_t *pNode, _Bool (*action)(void *pData))
{
    int count = 0;
    if( pNode == NULL)
        return 0;

    count = rev_inorder( pNode->right, action );   // R: Traverse the right
                                                   // subtree.
    if ( action( pNode->data ))                    // N: Visit the current
      ++count;                                     // node itself.
    count += rev_inorder( pNode->left, action );   // L: Traverse the left
                                                   // subtree.
    return count;
}

// -------------------------------------------------------------------------------
static int preorder( Node_t *pNode, _Bool (*action)(void *pData));

int BST_preorder( BST_t *pBST, _Bool (*action)(void *pData))
{
    if( pBST == NULL || action == NULL)
        return 0;
    else
        return preorder( pBST->pRoot, action);
}

// The recursive helper function preorder():
static int preorder( Node_t *pNode, _Bool (*action)(void *pData))
{
    int count = 0;
    if( pNode == NULL)
        return 0;

    if ( action( pNode->data ))                    // N: The current node.
      ++count;
    count += preorder( pNode->left, action );      // L: Traverse the left
                                                   // subtree.
    count += preorder( pNode->right, action );     // R: Traverse the right
                                                   // subtree.
    return count;
}

// -------------------------------------------------------------------------------
static int postorder( Node_t *pNode, _Bool (*action)(void *pData));

int BST_postorder( BST_t *pBST, _Bool (*action)(void *pData))
{
    if( pBST == NULL || action == NULL)
        return 0;
    else
        return postorder( pBST->pRoot, action);
}

// The recursive helper function postorder():
static int postorder( Node_t *pNode, _Bool (*action)(void *pData))
{
    int count = 0;
    if( pNode == NULL)
        return 0;

    count = postorder( pNode->left, action );      // L: Traverse the left
                                                   // subtree.
    count += postorder( pNode->right, action );    // R: Traverse the right
                                                   // subtree.
    if ( action( pNode->data ))                    // N: Visit the current
      ++count;                                     // node itself.

    return count;
}
