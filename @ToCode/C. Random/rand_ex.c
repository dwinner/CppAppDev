// rand_ex.c : rand() example
// -------------------------------------------------------------

#include <stdlib.h>       // int rand( void );
#include <time.h>
#include <ctype.h>
#include <stdio.h>

int main()
{
    printf( "Think of a number between one and twenty.\n"
            "Press Enter when you're ready." );
    getchar();

    srand( (unsigned)time( NULL ) );
    for ( int i = 0; i < 3; i++ )     // We get three guesses.
    {
        printf( "Is it %u? (y or n) ", 1 + rand() % 20 );
        if ( tolower( getchar() ) == 'y' )
        {
            printf( "Ha! I knew it!\n" );
            exit( 0 );
        }
        getchar();                     // Discard newline character.
    }
    printf( "I give up.\n" );

    return 0;
}
