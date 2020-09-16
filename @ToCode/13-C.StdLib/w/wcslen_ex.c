// wcslen_ex.c : wcslen() example
// -------------------------------------------------------------

#include <wchar.h>   // size_t wcslen( const wchar_t *s );

int main()
{
    wchar_t line[1024] =
            L"This string could easily be 400 or 500 characters long. "
            L"This string could easily be 400 or 500 characters long. "
            L"\n";
    wchar_t *readptr = line;

    int columns = 80;
    while( wcslen( readptr ) > columns)  // While remaining text is too long,
    {                                    // print a chunk with a final
       wprintf(L"%.*ls\\\n", columns-1, readptr);  // backslash and newline.
       readptr += columns -1;
    }
    wprintf( L"%ls\n", readptr);     // Print the rest, ending with a newline.

    return 0;
}
