// wcscspn_ex.c : wcscspn() example
// -------------------------------------------------------------

#include <wchar.h>  // size_t wcscspn( const wchar_t *s1, const wchar_t *s2 );
#include <stdio.h>

int main()
{
    wchar_t *path = L"/usr/local/bin:/usr/bin:/bin:/usr/bin/X11:/usr/games";
    int separator;

    wchar_t *basename = L"aprogram";
    wchar_t fullname[1024] = L"";

    separator = wcscspn( path, L":" );  // Obtain the index of the first colon.

    wcsncpy( fullname, path, separator );
    fullname[separator] = '\0';

    wcsncat( fullname, L"/", sizeof(fullname) - wcslen(fullname) -1 );
    wcsncat( fullname, basename, sizeof(fullname) - wcslen(fullname) -1 );

    fputws( fullname, stdout );

    return 0;
}
