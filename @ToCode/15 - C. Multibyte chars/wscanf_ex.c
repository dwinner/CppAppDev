// wscanf_ex.c : wscanf() example
// -------------------------------------------------------------

#include <stdio.h>
#include <wchar.h>
    // int wscanf( const wchar_t * restrict format, ... );
    // int wscanf_s( const wchar_t * restrict format, ... );

int main()
{
    wchar_t perms[12];
    wchar_t name[256];
    unsigned int ownerid, groupid, links;
    unsigned long size;
    int count;

    count = wscanf( L"%11l[rwxsStTld-+]%u%u%u%lu%*10s%*5s%256ls",
                    perms, &links, &ownerid, &groupid, &size, name );

wprintf(L"%ls %u %u %u %lu %ls\n", 
         perms, links, ownerid, groupid, size, name );
    wprintf( L"\nThe file %ls has a length of %lu bytes.\n", name, size );

    return 0;
}
