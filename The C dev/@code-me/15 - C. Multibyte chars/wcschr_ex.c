// wcschr_ex.c : wcschr() example
// -------------------------------------------------------------

#include <wchar.h>   // wchar_t *wcschr( const wchar_t *s, wchar_t c );
#include <stdio.h>
#include <stdlib.h>

typedef struct { wchar_t street[32];
                 wchar_t city[32];
                 wchar_t stateprovince[32];
                 wchar_t zip[16];
               } Address;

wchar_t printaddr[128] = L"720 S. Michigan Ave.\nChicago, IL 60605\n";

int main()
{
    int sublength;
    Address *newAddr = calloc( 1, sizeof(Address) );

    if ( newAddr != NULL )
    {
        sublength = wcschr( printaddr, L'\n' ) - printaddr;
        wcsncpy( newAddr->street, printaddr,
                 (sublength < 31 ? sublength : 31) );
        /* ... */
        fputws( newAddr->street, stdout );
    }
    return 0;
}
