// iswalnum_ex.c : iswalnum() example
// -------------------------------------------------------------

#include <wctype.h>     // int iswalnum( wint_t wc );
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
    wint_t wc;
    int i, dummy;

    setlocale( LC_CTYPE, "" );
    wprintf( L"\nThe current locale for the 'is ...' functions is '%s'.\n",
             setlocale( LC_CTYPE, NULL ) );

    wprintf( L"These are the alphanumeric wide characters"
             " in this locale:\n\n" );
    for ( wc = 0, i = 0; wc < 1024; wc++ )
    if ( iswalnum( wc ) )
    {
       if ( i % 25 == 0 )
       {
           wprintf( L"... more ...\n" );
           dummy = getchar();              // Wait before printing more
           wprintf( L"Wide character Code\n" );
           wprintf( L"-----------------------\n" );
       }
       wprintf( L"%5lc %4lu\n", wc, wc );
       i++;
    }
    wprintf( L"-----------------------\n" );

    return 0;
}
