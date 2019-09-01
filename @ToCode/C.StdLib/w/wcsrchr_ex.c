// wcsrchr_ex.c : wcsrchr() example
// -------------------------------------------------------------

#include <wchar.h>  // wchar_t *wcsrchr( const wchar_t *s, wchar_t wc );
#include <stdlib.h>

int main( int argc, char ** argv )
{
    wchar_t wmyname[256];

    size_t result = mbstowcs( wmyname, argv[0], 256 );
    if ( result == -1 )
       return -1;

    wchar_t *mybasename = wcsrchr( wmyname, L'/' ); // End of path
    if ( mybasename != NULL )
      mybasename++;
    else
      mybasename = wmyname;

    wprintf( L"This program was invoked as %ls.\n", mybasename );
}
