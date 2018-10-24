// isReadWriteable.c : 
// The function isReadWriteable() tests whether the file exists and 
// may be opened for reading and writing access.
// -----------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>

_Bool isReadWriteable( const char *filename )
{
    FILE *fp = fopen( filename, "r+" );    // Open a file to read and write.

    if ( fp != NULL )                      // Did fopen() succeed?
    {
        fclose(fp);                        // Yes: close the file; no error handling.
        return true;
    }
    else                                   // No.
        return false;
}

int main()
{
    char *file = "isReadWriteable.c";
    if( isReadWriteable( file) )
       printf("The file \"%s\" may be opened for read and write operations.\n",
               file);
    else
       printf("The file \"%s\" does not exist or can not be opened "
              "for reading and writing.\n", file);
    return 0;
}
