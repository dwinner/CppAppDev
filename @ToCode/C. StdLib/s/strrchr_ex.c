// strrchr_ex.c : strrchr() example
// -------------------------------------------------------------

#include <string.h>     // char *strrchr( const char *s, int c );
#include <stdio.h>

int main( int argc, char *argv[])
{
    char *mybasename = strrchr( argv[0], '/' );       // Find end of path.
    if ( mybasename != NULL )
        mybasename++;       // Point to the first character after the slash.
    else
        mybasename = argv[0];

    printf( "This program was invoked as %s.\n", mybasename );
    return 0;
}
