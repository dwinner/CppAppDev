#include "sparseTree.h"
#include <stdlib.h>
#include <string.h>

TreeCell* build_tree(TreeCell* root, TreeCell* base_node, TreeCell* node_to_insert)
{
	if (!base_node) /* first node in subtree */
	{
		node_to_insert->left = NULL;
		node_to_insert->right = NULL;
		if (!root)
		{
			return node_to_insert; /* first entry in tree */
		}

		if (strcmp(node_to_insert->cell_name, root->cell_name) < 0)
		{
			root->left = node_to_insert;
		}
		else
		{
			root->right = node_to_insert;
		}

		return node_to_insert;
	}

	if (strcmp(base_node->cell_name, node_to_insert->cell_name) <= 0)
	{
		build_tree(base_node, base_node->right, node_to_insert);
	}
	else
	{
		build_tree(base_node, base_node->left, node_to_insert);
	}

	return root;
}

TreeCell* delete_tree_item(TreeCell* root, char* key)
{
	TreeCell* p;
	if (!root)
	{
		return root; /* item not found */
	}

	if (!strcmp(root->cell_name, key)) /* delete root */
	{
		if (root->left == root->right) /* this means an empty tree */
		{
			free(root);
			return NULL;
		}
		if (root->left == NULL) /* or if one subtree is null */
		{
			p = root->right;
			free(root);
			return p;
		}
		if (root->right == NULL)
		{
			p = root->left;
			free(root);
			return p;
		}
		/* or both subtrees present */
		TreeCell* p2 = root->right;
		p = root->right;
		while (p->left)
		{
			p = p->left;
		}

		p->left = root->left;
		free(root);

		return p2;
	}

	if (strcmp(root->cell_name, key) <= 0)
	{
		root->right = delete_tree_item(root->right, key);
	}
	else
	{
		root->left = delete_tree_item(root->left, key);
	}

	return root;
}

TreeCell* search_tree(TreeCell* root, char* key)
{
	if (!root) /* empty tree */
	{
		return root;
	}

	while (strcmp(root->cell_name, key) != 0)
	{
		if (strcmp(root->cell_name, key) <= 0)
		{
			root = root->right;
		}
		else
		{
			root = root->left;
		}

		if (root == NULL)
		{
			break;
		}
	}

	return root;
}
