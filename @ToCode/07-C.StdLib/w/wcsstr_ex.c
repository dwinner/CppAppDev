// wcsstr_ex.c : wcsstr() example
// -------------------------------------------------------------

#include <wchar.h>     // size_t wcsstr( const wchar_t *s1,
                       //                const wchar_t *s2 );
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE 1024

int main( int argc, char **argv )
{
    FILE *fpIn = NULL;
    wchar_t keyword[MAX_LINE] = { L'\0' };
    wchar_t line[MAX_LINE] = { L'\0' };

    if ( argc != 3 )
    {
        wprintf( L"Syntax: %s <keyword> <filename>\n", argv[0] );
        return -1;
    }

    if (( fpIn = fopen( argv[2], "r" )) == NULL )
       return -2;
    else
       fwide( fpIn, 1 );

    if ( mbstowcs( keyword, argv[1], MAX_LINE ) == -1 )
       return -3;

    int count = 0;
    while ( fgetws( line, MAX_LINE, fpIn ) != NULL )
       if ( wcsstr( line, keyword ) != NULL )
       {
           ++count;
           fputws( line, stdout );
       }

    if ( !feof( fpIn ))
       return -4;
    else
       return count;
}
