// putchar_ex.c : putchar() example
// -------------------------------------------------------------

// The following example reads the beginning of a file repetitively,
// and reports its progress on stdout.

#include <stdio.h>      // int putchar( int c );

int main()
{
    long count; const long CYCLES = 5000;
    char readback[1024];

    FILE *fp = fopen( "infile.txt", "r" );
    if( fp == NULL)
    { fprintf( stderr, "Couldn't open input file.\n" ); return -1; }

    for (count = 0; count <= CYCLES; ++count)
    {
      /* Start output with '\r' to re-use same screen line. */
       printf( "\rPerformed %li file reads. ", count );

       rewind( fp );
       fgets( readback, 1024, fp );

      /* Scroll a new screen line every hundred cycles. */
       if (count % 100 != 0) continue;
       putchar( '\n' );
    }
    puts( "Done." );
    return 0;
}
