// strlen_ex.c : strlen() example
// -------------------------------------------------------------

#include <string.h>  // size_t strlen( const char *s );
#include <stdio.h>

int main()
{
    char line[1024] =
         "This string could easily be hundreds of characters long.";
    char *readptr = line;
    int columns = 80;

    // While the text is longer than a row:
    while ( strlen( readptr ) > columns )
    {   // print a row with a backslash at the end:
        printf( "%.*s\\", columns-1, readptr);
        readptr += columns -1;
    }   
    // Then print the rest with a newline at the end:
    printf( "%s\n", readptr );

    return 0;
}
