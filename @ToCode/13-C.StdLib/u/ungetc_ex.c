// ungetc_ex.c : ungetc() example
// -------------------------------------------------------------

#include <stdio.h>       // int ungetc( int c, FILE *fp );
#include <stdlib.h>
#include <ctype.h>

int main()
{
    char file[ ] = "input.dat";
    FILE *fp;
    int c;
    char numstr[64];

    if (( fp = fopen( file, "r" )) == NULL )
       fprintf( stderr, "Can't read the file %s\n", file), exit(1);

    while ( (c = getc(fp)) != EOF )
    {
       if ( isdigit(c) )              // Collect a sequence of digits.
       {
          int i = 0;
          do
          {
             numstr[i++] = (char)c;
             c = getc(fp);
          }while ( isdigit(c) && i+1 < sizeof(numstr) );

          numstr[i] = '\0';            // Terminate the numeral string.

          /* ... process the numeral string ... */
          puts( numstr);

          if ( ungetc( c, fp) == EOF)  // Put back the first non-digit.
             break;
          continue;
       }

       /* ... process any non-digit characters ... */
    }
    if ( !feof( fp))
       fprintf( stderr, "Error processing the file %s\n", file);

    return 0;
}
