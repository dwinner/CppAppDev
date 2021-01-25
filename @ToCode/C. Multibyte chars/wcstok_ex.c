// wcstok_ex.c : wcstok() example
// -------------------------------------------------------------

#include <wchar.h>     // wchar_t *wcstok( wchar_t * restrict s1, 
                       //                  const wchar_t * restrict s2,
                       //                  wchar_t ** restrict ptr );

int main()
{
    wchar_t *mnemonic, *arg1, *arg2, *comment, *ptr;
    wchar_t line[ ] = L" mul eax,[ebp+4] ; Multiply by y\n";

    // First word between spaces or tabs
    mnemonic = wcstok( line, L" \t", &ptr );
    arg1 = wcstok( NULL, L",", &ptr );    // From there to the comma is arg1.
                                          // Trim off any spaces later.
    arg2 = wcstok( NULL, L";\n", &ptr );  // From there to the semicolon is
                                          // arg2.
    // To line or page end is comment:
    comment = wcstok( NULL, L"\n\r\v\f", &ptr );

    wprintf( L"Mnemonic:     %ls\n"
             L"1st argument: %ls\n"
             L"2nd argument: %ls\n"
             L"Comment:      %ls\n\n",
             mnemonic, arg1, arg2, comment );

    return 0;
}
