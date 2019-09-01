#pragma once

/**
 *	E-Table cell
 */
struct tree_cell
{
	/**
	 *	cell name e.g., A1, B34
	 */
	char cell_name[9];

	/**
	 *	info e.g., 10/B2
	 */
	char formula[128];

	/**
	 *	Pointer to left subtree
	 */
	struct tree_cell *left;

	/**
	 *	Pointer to right subtree
	 */
	struct tree_cell *right;
};

typedef struct tree_cell TreeCell;

/**
 * \brief Build tree
 * \param root 
 * \param base_node 
 * \param node_to_insert 
 * \return 
 */
TreeCell* build_tree(TreeCell* root, TreeCell* base_node, TreeCell* node_to_insert);

/**
 * \brief Delete item from the tree
 * \param root 
 * \param key 
 * \return 
 */
TreeCell* delete_tree_item(TreeCell* root, char* key);

/**
 * \brief Search item in tree
 * \param root 
 * \param key 
 * \return 
 */
TreeCell* search_tree(TreeCell* root, char* key);
