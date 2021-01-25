// fgets_ex.c : fgets() example
// -------------------------------------------------------------

#include <stdio.h>   // char *fgets( char * restrict buffer, int n,
                     //              FILE * restrict fp );
#include <string.h>

int main()
{
    FILE *titlefile;
    char title[256];
    int counter = 0;

    if ((titlefile = fopen("titles.txt", "r")) == NULL)
       perror( "Opening title file" );
    else
    {
       while ( fgets( title, 256, titlefile ) != NULL )
       {
          title[ strlen(title) -1 ] = '\0';   // Trim off newline character.
          printf( "%3d: \"%s\"\n", ++counter, title );
       }
       /* fgets() returned NULL: either EOF or an error occurred. */
       if ( feof(titlefile) )
         printf("Total: %d titles.\n", counter);
    }
    fclose( titlefile );
    return 0;
}
