// wcstoumax_ex.c : wcstoumax() example
// -------------------------------------------------------------

#include <stddef.h>
#include <inttypes.h>  // uintmax_t wcstoumax( const wchar_t * restrict wcs,
                       //                      wchar_t ** restrict endptr, int base );
#include <wchar.h>

typedef struct {
    uintmax_t packets, bytes;
    wchar_t policy[16];
    wchar_t protocol[6];
    /* ... */
} stats_t ;

int main()
{
    stats_t iface_in = {0};
    wchar_t wcsstat[] =
            L"25183 1633438 ACCEPT tcp -- eth2 * 0.0.0.0/0 tcp dpts:80";
    wchar_t *wcsptr = wcsstat;

    iface_in.packets = wcstoumax( wcsptr, &wcsptr, 10 );
    iface_in.bytes = wcstoumax( ++wcsptr, &wcsptr, 10 );
    /* ... */

    wprintf( L"Packets: %" PRIuMAX "; bytes: %" PRIuMAX "; policy: ...\n",
             iface_in.packets, iface_in.bytes );

    return 0;
}
