// signal_ex.c : signal() example
// -----------------------------------------------------------------------

#include <signal.h>   // void ( *signal( int sig, void (*handler)(int) ) )(int);
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>   // Defines SIG_ATOMIC_MAX

void sigint_handler(int sig);
volatile sig_atomic_t i;   // A counter accessed by main and the
                           // handler.

int main()
{
    if ( signal( SIGINT, sigint_handler ) == SIG_ERR )
    {
        perror("Failed to install SIGINT handler");
        exit(3);
    }

    while (1)
    {
        puts( "Press Ctrl+C to interrupt me.");
        for ( i = 0 ; i < SIG_ATOMIC_MAX ; i++ )
            if ( i % 100000 == 0)
            {
                printf( "\r%d ", i / 100000 );
                fflush( stdout );
            }
        raise( SIGINT );   // Simulate a Ctrl+C in case the user didn't
                           // type it.
    }
    return 0;
}

void sigint_handler( int sig )
{
    int c = 0;

    if ( sig != SIGINT ) exit( 1 );

    signal( SIGINT, SIG_IGN );         // Ignore a second Ctrl+C

    puts( "\nThis is the function sigint_handler()."
          "\nDo you want to exit the program now? [y/n]");
    while (( c = tolower( getchar( ) )) != 'y' && c != 'n' && c != EOF )
      ;

    if ( c != 'n' )
       exit(0);
    else
       i = 0;                          // Reset timer

    signal( SIGINT, sigint_handler );  // Reinstall this handler.

    /* No return value; just fall off the end of the function. */
}
