// strchr_ex.c : strchr() example
// -------------------------------------------------------------

#include <string.h>  // char *strchr( const char *s, int c );
#include <stdio.h>
#include <stdlib.h>

typedef struct { char street[32];
                 char city[32];
                 char stateprovince[32];
                 char zip[16];
               } Address;

char printaddr[128] = "720 S. Michigan Ave.\nChicago, IL 60605\n";

int main()
{
    int sublength;
    Address *newAddr = calloc( 1, sizeof(Address) );

    if ( newAddr != NULL )
    {
        sublength = strchr( printaddr, '\n' ) - printaddr;
        strncpy( newAddr->street, printaddr,
                 ( sublength < 31 ? sublength : 31 ) );
        /* ... */
        puts(newAddr->street);
    }
    return 0;
}
