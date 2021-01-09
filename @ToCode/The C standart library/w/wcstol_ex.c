// wcstol_ex.c : wcstol(), wcstoll() example
// -------------------------------------------------------------

#include <wchar.h>     // long int wcstol( const wchar_t * restrict wcs,
                       //                  wchar_t ** restrict endptr, int base );
                       // long long int wcstoll( const wchar_t * restrict wcs,
                       //                        wchar_t ** restrict endptr, 
                       //                        int base );

int main()
{
    wchar_t date[ ] = L"10/3/2005, 13:44:18 +0100", *more = date;
    long day, mo, yr, hr, min, sec, tzone;

    day = wcstol( more, &more, 10 ); // &more is the address of a
    mo  = wcstol( more+1, &more, 10 ); // pointer
    yr  = wcstol( more+1, &more, 10 );
    hr  = wcstol( more+1, &more, 10 );
    min = wcstol( more+1, &more, 10 );
    sec = wcstol( more+1, &more, 10 );
    tzone = wcstol( more+1, &more, 10 );

    wprintf( L"It's now %02ld:%02ld o'clock on %02ld-%02ld-%02ld.\n",
             hr, min, mo, day, yr % 100 );

    return 0;
}
