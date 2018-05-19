// rewind_ex.c : rewind() example
// This example prints the contents of a file twice, converting 
// each character to lowercase the first time through, and to 
// uppercase the second time:
// -------------------------------------------------------------

#include <stdio.h>   // void rewind( FILE *fp );
#include <stdlib.h>
#include <ctype.h>

int main( int argc, char *argv[])
{
    FILE *fp; int c;

    if ( argc != 2 )
       printf( "Usage: program input-file\n"), exit(1);

    if (( fp = fopen( argv[1], "r" )) == NULL )
        fprintf( stderr, "Failed to open file %s\n", argv[1] );
    else
    {
        puts( "Contents of the file in lowercase:" );
        while (( c = fgetc( fp )) != EOF )
            putchar( tolower( c ));

        rewind( fp );

        puts( "Same again in uppercase:" );
        while (( c = fgetc( fp )) != EOF )
            putchar( toupper( c ));

       fclose( fp );
    }
    return 0;
}
