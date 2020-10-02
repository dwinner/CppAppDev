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
static bool internal_insert(BstT* pBst, NodeT** ppNode, const void* pData, size_t size);

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
static _Bool internal_erase(BstT *pBst, NodeT **ppNode, const void *pKey);

/**
 * \brief Plucks the minimum node from a specified subtree, and returns 
 * \param ppNode Pointer to pointer to the starting node
 * \return A pointer to the detached node
 */
static NodeT *detach_min(NodeT **ppNode);

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

bool bst_insert(BstT* pBst, const void* pData, size_t size)
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
}

/************************************************************************/
/* Internal functions                                                   */
/************************************************************************/

const void* default_get_key(const void* pData)
{
	return pData;
}

static bool internal_insert(BstT* pBst, NodeT** ppNode, const void* pData, size_t size)
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

static _Bool internal_erase(BstT *pBst, NodeT **ppNode, const void *pKey)
{
	return false;
}

static NodeT *detach_min(NodeT **ppNode)
{
	return NULL;
}
