#include "sparseTree.h"
#include <stdlib.h>
#include <string.h>

list_entry* build_tree(list_entry* root, list_entry* base_node, list_entry* node_to_insert)
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
