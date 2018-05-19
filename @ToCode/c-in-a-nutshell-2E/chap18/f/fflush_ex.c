// fflush_ex.c : fflush() example
// -------------------------------------------------------------

#include <stdio.h>   // int fflush( FILE *fp );
#include <signal.h>

/* Tests the effect of flushing output file buffers. */

int main()
{
    FILE *fp;

#ifdef FLUSH
    char filename[ ] = "twice.txt";
#else
    char filename[ ] = "once.txt";
#endif  /* FLUSH */

    fp = fopen( filename, "w" );
    if ( fp == NULL)
       fprintf( stderr, "Failed to open file '%s' to write.\n", filename );

    fputs( "Going once ...\n", fp );
    fflush( fp );                 // Flush the output unconditionally

    fputs( "Going twice ...\n", fp );

#ifdef FLUSH
    fflush( fp );                 // Now flush only if compiled with '-DFLUSH'
#endif

    raise( SIGKILL );             // End the program abruptly.

    fputs( "Gone.\n", fp );       // These three lines will never be executed.
    fclose( fp );
    return 0;
}
