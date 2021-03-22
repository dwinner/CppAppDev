// swprintf_ex.c : swprintf() example
// -------------------------------------------------------------

#include <wchar.h>  // int swprintf( wchar_t * restrict dest, size_t n,
                    //               const wchar_t * restrict format, ... );
#include <stdlib.h>

const wchar_t *dollar_as_wstr( long amount)
// Converts a number of cents into a wide string
// showing dollars and cents.
// For example, converts -123456 into the wide string L"-$1234.56"
{
    static wchar_t buffer[16];
    wchar_t sign[2] = L"";

    if ( amount < 0L)
       amount = -amount, sign[0] = '-';

    ldiv_t dollars_cents = ldiv( amount, 100);
    swprintf( buffer, sizeof(buffer),
              L"%ls$%ld.%2ld", sign, dollars_cents.quot, dollars_cents.rem);

    return buffer;
}

#include <stdio.h>

int main()
{
    fputws( dollar_as_wstr( -123456), stdout );
    return 0;
}
