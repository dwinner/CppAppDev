// Example 12-3. The sortlines program
// sortlines.c

// This program reads each line of text into a node of a binary tree,
// and then prints the text in sorted order.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BSTree.h"               // Prototypes of the BST functions.

#define LEN_MAX 1000              // Maximum length of a line.
char buffer[LEN_MAX];

// Action to perform for each line:
_Bool printStr( void *str ) { return printf( "%s", str ) >= 0; }

int main()
{
    BST_t *pStrTree = newBST( (CmpFunc_t*)strcmp, NULL );
    int n;

    while ( fgets( buffer, LEN_MAX, stdin ) != NULL )   // Read each line.
    {
       size_t len = strlen( buffer );                   // Length incl.
                                                        // newline character.
       if ( !BST_insert( pStrTree, buffer, len+1 ))     // Insert the line in
          break;                                        // the tree.
    }
    if ( !feof(stdin) )
    {                                     // If unable to read the entire text:
       fprintf( stderr, "sortlines: "
                "Error reading or storing text input.\n" );
       exit( EXIT_FAILURE );
    }

    n = BST_inorder( pStrTree, printStr );     // Print each line, in sorted order.

    fprintf( stderr, "\nsortlines: Printed %d lines.\n", n );

    BST_clear( pStrTree );                     // Discard all nodes.
    return 0;
}
