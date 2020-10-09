#include <string.h>
#include <stdlib.h>
#include "bs_tree.h"

/************************************************************************/
/* Forward declarations                                                 */
/************************************************************************/

/**
 * \brief Default function for getting key by data
 * \param pData Data
 * \return Key by data
 */
const void* default_get_key(const void* pData);

/**
 * \brief Inserts the new leaf at a position that is consistent with the binary tree’s sorting condition.
 * \param pBst Tree
 * \param ppNode Pointer to pointer to the node (to change the original address it if it's nessesary)
 * \param pData Data
 * \param size Data size
 * \return true if it succeeds in inserting the new data, false - otherwise
 */
static bool internal_insert(BstT* pBst, NodeT** ppNode, const void* pData, const size_t size);

/**
 * \brief Uses the binary search algorithm to find a data item that matches a given key
 * \param pBst Tree
 * \param pNode Starting node where the search begins
 * \param pKey Key
 * \return A pointer to the data item of the first node that matches the key, or a null pointer if no match was found
 */
static const void* internal_search(BstT* pBst, const NodeT* pNode, const void* pKey);

/**
 * \brief Searches for a node that matches the specified key, and deletes it if found.
 * \param pBst Tree
 * \param ppNode Pointer to pointer to the starting node
 * \param pKey Key to search
 * \return false if it fails to find a matching node to delete, or true if successful
 */
static bool internal_erase(BstT* pBst, NodeT** ppNode, const void* pKey);

/**
 * \brief Plucks the minimum node from a specified subtree, and returns 
 * \param ppNode Pointer to pointer to the starting node
 * \return A pointer to the detached node
 */
static NodeT* detach_min(NodeT** ppNode);

/**
 * \brief Deletes all the nodes of a tree
 * \param pNode The tree root
 */
static void internal_clear(NodeT* pNode);

/**
 * \brief Traverses the tree in post order
 * \param pNode The root node
 * \param action Traverse action
 * \return Traversed node's count
 */
static int post_order(NodeT* pNode, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in pre order
 * \param pNode The root node
 * \param action Traverse action
 * \return Traversed node's count
 */
static int pre_order(NodeT* pNode, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in reverse order
 * \param pNode The root node
 * \param action Traverse action
 * \return Traversed node's count
 */
static int rev_inorder(NodeT* pNode, bool (*action)(void* pData));

/**
 * \brief Traverses the tree in direct order
 * \param pNode The root node
 * \param action Traverse action
 * \return Traversed node's count
 */
static int in_order(NodeT* pNode, bool (*action)(void* pData));

/************************************************************************/
/* External functions                                                   */
/************************************************************************/

BstT* new_bst(CmpFuncT* cmp, GetKeyFuncT* getKey)
{
	BstT* pBst = NULL;

	if (cmp != NULL)
	{
		pBst = malloc(sizeof(BstT));
	}

	if (pBst != NULL)
	{
		pBst->p_root = NULL;
		pBst->cmp = cmp;
		pBst->get_key = getKey != NULL
			                ? getKey
			                : default_get_key;
	}

	return pBst;
}

bool bst_insert(BstT* pBst, const void* pData, const size_t size)
{
	return pBst == NULL || pData == NULL || size == 0
		       ? false
		       : internal_insert(pBst, &pBst->p_root, pData, size);
}

const void* bst_search(BstT* pBst, const void* pKey)
{
	return pBst == NULL || pKey == NULL
		       ? NULL
		       : internal_search(pBst, pBst->p_root, pKey);
}

bool bst_erase(BstT* pBst, const void* pKey)
{
	return pBst == NULL || pKey == NULL
		       ? false
		       : internal_erase(pBst, &pBst->p_root, pKey); // Start at the root of the tree.
}

void bst_clear(BstT* pBst)
{
	if (pBst != NULL)
	{
		internal_clear(pBst->p_root);
		pBst->p_root = NULL;
	}
}

int bst_inorder(BstT* pBst, bool (* action)(void* pData))
{
	return pBst == NULL || action == NULL
		       ? 0
		       : in_order(pBst->p_root, action);
}

int bst_rev_inorder(BstT* pBst, bool (* action)(void* pData))
{
	return pBst == NULL || action == NULL
		       ? 0
		       : rev_inorder(pBst->p_root, action);
}

int bst_preorder(BstT* pBst, bool (* action)(void* pData))
{
	return pBst == NULL || action == NULL
		       ? 0
		       : pre_order(pBst->p_root, action);
}

int bst_postorder(BstT* pBst, bool (* action)(void* pData))
{
	return pBst == NULL || action == NULL
		       ? 0
		       : post_order(pBst->p_root, action);
}

/************************************************************************/
/* Internal functions                                                   */
/************************************************************************/

const void* default_get_key(const void* pData)
{
	return pData;
}

static bool internal_insert(BstT* pBst, NodeT** ppNode, const void* pData, const size_t size)
{
	NodeT* pNode = *ppNode; // Pointer to the root node of the subtree to insert the new node in.

	if (pNode == NULL) // There's a place for a new leaf here.
	{
		pNode = malloc(sizeof(NodeT) + size);
		if (pNode != NULL)
		{
			pNode->left = pNode->right = NULL; // Initialize the new node's members
			memcpy(pNode->data, pData, size);
			*ppNode = pNode; // Insert the new node.

			return true;
		}

		return false;
	}

	// Continue looking for a place ...
	const void
		*key1 = pBst->get_key(pData),
		*key2 = pBst->get_key(pNode->data);
	return internal_insert(pBst, pBst->cmp(key1, key2) < 0
		                             ? &pNode->left // ... in the left subtree,
		                             : &pNode->right, // or in the right subtree.
	                       pData,
	                       size);
}

static const void* internal_search(BstT* pBst, const NodeT* pNode, const void* pKey)
{
	if (pNode == NULL)
	{
		return NULL; // No subtree to search; no match found.
	}

	// compare data
	const int cmpResult = pBst->cmp(pKey, pBst->get_key(pNode->data));
	return cmpResult == 0
		       ? pNode->data // Found a match.
		       : internal_search(pBst, cmpResult < 0 // Continue the search
			                               ? pNode->left // in the left subtree,
			                               : pNode->right, // or in the right subtree.
		                         pKey);
}

static bool internal_erase(BstT* pBst, NodeT** ppNode, const void* pKey)
{
	NodeT* pNode = *ppNode; // Pointer to the current node.

	if (pNode == NULL)
	{
		return false; // No match found.
	}

	// Compare data
	const int cmpRes = pBst->cmp(pKey, pBst->get_key(pNode->data));

	if (cmpRes < 0) // Continue the search in the left subtree,
	{
		return internal_erase(pBst, &pNode->left, pKey);
	}
	
	if (cmpRes > 0) // or in the right subtree.
	{
		return internal_erase(pBst, &pNode->right, pKey);
	}
	
	// Found the node to be deleted.
	if (pNode->left == NULL) // If no more than one child, attach the child to the parent.
	{
		*ppNode = pNode->right;
	}
	else if (pNode->right == NULL)
	{
		*ppNode = pNode->left;
	}
	else // Two children: replace the node with the minimum from the right subtree.
	{
		NodeT* pMin = detach_min(&pNode->right);
		*ppNode = pMin; // Graft it onto the deleted node's parent.
		pMin->left = pNode->left; // Graft the deleted node's children.
		pMin->right = pNode->right;
	}

	free(pNode); // Release the deleted node's storage.
	return true;
}

static NodeT* detach_min(NodeT** ppNode)
{
	NodeT* pNode = *ppNode; // A pointer to the current node.

	if (pNode == NULL) // pNode is an empty subtree.
	{
		return NULL;
	}
	
	if (pNode->left != NULL)
	{
		return detach_min(&pNode->left); // The minimum is in the left subtree.
	}
	
	// pNode points to the minimum node.
	*ppNode = pNode->right; // Attach the right child to the parent.
	return pNode;
}

static void internal_clear(NodeT* pNode)
{
	if (pNode != NULL)
	{
		internal_clear(pNode->left);
		internal_clear(pNode->right);
		free(pNode);
	}
}

static int post_order(NodeT* pNode, bool (*action)(void* pData))
{
	int count = 0;
	if (pNode == NULL)
	{
		return 0;
	}

	count = post_order(pNode->left, action); // L: Traverse the left subtree	
	count += post_order(pNode->right, action); // R: Traverse the right subtree

	if (action(pNode->data)) // N: Visit the current node itself.
	{
		++count;
	}

	return count;
}

static int pre_order(NodeT* pNode, bool (*action)(void* pData))
{
	int count = 0;
	if (pNode == NULL)
	{
		return 0;
	}

	if (action(pNode->data)) // N: The current node.
	{
		++count;
	}

	count += pre_order(pNode->left, action); // L: Traverse the left subtree	
	count += pre_order(pNode->right, action); // R: Traverse the right subtree

	return count;
}

static int rev_inorder(NodeT* pNode, bool (*action)(void* pData))
{
	int count = 0;
	if (pNode == NULL)
	{
		return 0;
	}

	count = rev_inorder(pNode->right, action); // R: Traverse the right subtree
	if (action(pNode->data)) // N: Visit the current node itself.
	{
		++count;
	}

	count += rev_inorder(pNode->left, action); // L: Traverse the left subtree.

	return count;
}

static int in_order(NodeT* pNode, bool (*action)(void* pData))
{
	int count = 0;
	if (pNode == NULL)
	{
		return 0;
	}

	count = in_order(pNode->left, action); // L: Traverse the left subtree.
	if (action(pNode->data)) // N: Visit the current
	{
		++count; // node itself.                                     
	}

	count += in_order(pNode->right, action); // R: Traverse the right subtree.

	return count;
}
