// tmpfile_ex.c : tmpfile(), tmpfile_s() example
// -------------------------------------------------------------

#include <stdio.h>   // FILE *tmpfile( void );
                     // errno_t tmpfile_s(FILE * restrict * restrict streamPtr);
#include <errno.h>

int main()
{
    FILE *fpTmp, *fpRx;
    int c;

    /* ... open Rx stream ... */
    fpRx = stdin;

    if (( fpTmp = tmpfile() ) == NULL )
    // or
    // if( tmpfile_s( &fpTmp) != 0 )
        fputs( "Unable to open a temporary file.", stderr );
    else
    {
        while (( c = fgetc( fpRx )) != EOF )
            if ( fputc( c, fpTmp ) == EOF )
               break;
    }
    fclose( fpRx );

    /* ... process the data captured in fpTmp ... */

    rewind( fpTmp);
    while( (c = fgetc( fpTmp)) != EOF)
       putchar(c);

    return 0;
}
