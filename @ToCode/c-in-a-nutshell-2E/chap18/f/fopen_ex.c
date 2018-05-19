// fopen_ex.c : fopen() example
// -------------------------------------------------------------

#include <stdio.h>   // FILE *fopen( const char * restrict name,
                     //              const char * restrict mode );
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[])
{
    FILE *in, *out;
    int c;

    if ( argc != 3 )
       fprintf( stderr, "Usage: program input-file output-file\n"), exit(1);

    // If "-" appears in place of input filename, use stdin:
    in = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1], "r");
    if ( in == NULL )
    {  perror( "Opening input file" ); return -1;  }

    // If "-" appears in place of output filename, use stdout:
    out = (strcmp(argv[2], "-") == 0) ? stdout : fopen(argv[2], "a+");
    if ( out == NULL )
    {   perror( "Opening output file" ); return -1; }

    while (( c = fgetc( in )) != EOF)
       if ( fputc(c, out) == EOF )
          break;

    if ( !feof( in ))
       perror( "Error while copying" );

    fclose(in), fclose(out);
    return 0;
}
