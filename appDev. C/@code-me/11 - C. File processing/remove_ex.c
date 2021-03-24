// remove_ex.c : remove() example
// -------------------------------------------------------------

#include <stdio.h>     // int remove( const char *filename );
#include <errno.h>

int main()
{
    char fname_tmp[L_tmpnam] = "";
    FILE *fp;
    int result;

    tmpnam( fname_tmp );
    fp = fopen( fname_tmp, "w+" );
    if( fp == NULL)
    {  fprintf(stderr, "Couldn't open file \"%s\".\n", fname_tmp);
       return -1;
    }

    /* ... write something in the file, edit it ... */
    fputs( "hello ...\n", fp);

    fclose( fp );

    result = rename( fname_tmp, "finished.txt" );
    if ( result )     // Delete previous "finished.txt" and try again.
    {
        remove( "finished.txt" );
        result = rename( fname_tmp, "finished.txt" );
        if ( result )                   // Give up and log the error.
           fprintf( stderr, "Error %d on trying to rename output file\n",
                                                                   errno );
    }
    return 0;
}
