// wctomb_ex.c : wctomb() example
// -------------------------------------------------------------

#include <stdlib.h>   // int wctomb( char *s, wchar_t wc );
#include <wchar.h>
#include <stdio.h>
#include <limits.h>
#include <locale.h>

int main()
{
    char mbbuffer[MB_LEN_MAX] = { '\0' };
    wchar_t wcs[] = L"Wir stehen auf den Füßen von Riesen";
    int n = 0, i = 0;

    printf( "The current locale is %s.\n", setlocale( LC_CTYPE, "" ));
    printf( "The locale's multibyte encoding is %s.\n",
             (wctomb( NULL, L'\0' ) ? "stateful" : "stateless" ));

    do {
        n += wctomb( mbbuffer, wcs[i] );
    } while ( wcs[i++] != L'\0' );

    printf( "The wide string \"%ls\" \nis %u wide characters long.\n"
            "Its multibyte representation requires a buffer of %u bytes.\n",
            wcs, wcslen( wcs ), n );

    return 0;
}
