// wcsrtombs_ex.c : wcsrtombs() example
// -------------------------------------------------------------

#include <wchar.h>   // size_t wcsrtombs( char * restrict dest,
                     //                   const wchar_t **restrict src,
                     //                   size_t n, 
                     //                   mbstate_t * restrict state );
#include <string.h>
#include <locale.h>
#include <stdio.h>

int main()
{
    int i = 0, n = 0;
    size_t result;
    wchar_t wc;
    char mbstring[256] = { '\0' };

    wchar_t widestring[]
            = L"This is originally a string of wide characters.";
    const wchar_t *wcsptr = widestring;
    mbstate_t state;

    printf( "The current locale is %s.\n", setlocale(LC_CTYPE, "") );

    memset( &state, '\0', sizeof state );
    result = wcsrtombs( mbstring, &wcsptr, 256, &state );

    printf("The return value: %d\n", (int)result );
    if( result > 0 && wcsptr == NULL )
       printf("The multibyte string: \"%s\"\n", mbstring);

   return 0;
}
