#pragma once

/**
 *	E-Table cell
 */
struct cell
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
	struct cell *left;

	/**
	 *	Pointer to right subtree
	 */
	struct cell *right;
};

typedef struct cell list_entry;


/**
 * \brief 
 * \param root 
 * \param base_node 
 * \param node_to_insert 
 * \return 
 */
list_entry *build_tree(list_entry *root, list_entry *base_node, list_entry *node_to_insert);
