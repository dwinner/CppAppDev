// Example 7-6. The command line
// args.c

#include <stdio.h>

int main( int argc, char *argv[ ] )
{
    if ( argc == 0 )
    puts( "No command line available." );
    else
    {                                    // Print the name of the program.
        printf( "The program now running: %s\n", argv[0] );
        if ( argc == 1 )
            puts( "No arguments received on the command line." );
        else
        {
            puts( "The command-line arguments:" );
            for ( int i = 1; i < argc; ++i )   // Print each argument on
                puts( argv[i] );               // a separate line.
        }
    }
}
