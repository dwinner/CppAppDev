// fwprintf_ex.c : fwprintf() example
// -------------------------------------------------------------

#include <stdio.h>     // int fwprintf( FILE * restrict fp,
#include <wchar.h>     //               const wchar_t * restrict format, ... );
                       // int fwprintf_s( FILE * restrict fp,
                       //                 const wchar_t * restrict format, ...);
#include <wchar.h>
#include <locale.h>

int main()
{
    wchar_t name_local[ ] = L"Ka\u0142u\u017Cny";
    char name_portable[ ]= "Kaluzny";
    char locale[ ] = "pl_PL.UTF-8";
    char * newlocale;

    newlocale = setlocale( LC_ALL, locale );
    if ( newlocale == NULL )
       fprintf( stderr, "Sorry, couldn't change the locale to %s.\n"
                "The current locale is %s.\n",
                locale, setlocale( LC_ALL, NULL ));

    fwprintf( stdout,
              L"Customer's name: %ls (Single-byte transliteration: %s)\n",
              name_local, name_portable );

    return 0;
}
