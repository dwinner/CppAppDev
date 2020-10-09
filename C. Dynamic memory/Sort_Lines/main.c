/**
 * This program reads each line of text into a node of a binary tree,
 * and then prints the text in sorted order.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bs_tree.h"

/*#ifdef __cplusplus
extern "C"
{
#endif

extern BstT* new_bst(CmpFuncT* cmp, GetKeyFuncT* getKey);

#ifdef __cplusplus
}
#endif*/

#define LEN_MAX 1000              // Maximum length of a line.
char buffer[LEN_MAX];

// Action to perform for each line:
bool print_str(void* str)
{
	return printf("%s", (const char*)str) >= 0;
}

int main()
{
	BstT* pStrTree = new_bst((CmpFuncT*)strcmp, NULL);
	int n;

	while (fgets(buffer, LEN_MAX, stdin) != NULL) // Read each line.
	{
		size_t len = strlen(buffer); // Length incl.

		// newline character.
		if (!bst_insert(pStrTree, buffer, len + 1)) // Insert the line in the tree.
		{
			break;
		}
	}

	if (!feof(stdin)) // If unable to read the entire text:
	{
		fprintf(stderr, "sortlines: "
		        "Error reading or storing text input.\n");
		exit(EXIT_FAILURE);
	}

	n = bst_inorder(pStrTree, print_str); // Print each line, in sorted order.

	fprintf(stderr, "\nsortlines: Printed %d lines.\n", n);

	bst_clear(pStrTree); // Discard all nodes.

	return EXIT_SUCCESS;
}
