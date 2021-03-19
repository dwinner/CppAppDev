// iswctype_ex.c : iswctype() example
// -------------------------------------------------------------

#include <wctype.h>    // int iswctype( wint_t wc, wctype_t description );
#include <wchar.h>
#include <locale.h>

int main()
{
    wint_t wc = L'ß';

    setlocale( LC_CTYPE, "de_DE.UTF-8" );
    if ( iswctype( wc, wctype( "alpha" )) )
    {
        if ( iswctype( wc, wctype( "lower" ) ))
           wprintf( L"The character %lc is lowercase.\n", wc );
        if ( iswctype( wc, wctype( "upper" ) ))
           wprintf( L"The character %lc is uppercase.\n", wc );
    }
    return 0;
}
