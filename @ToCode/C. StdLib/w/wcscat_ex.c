// wcscat_ex.c : wcscat(), wcscat_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1   // for wcscat_s()

#include <wchar.h>
   // wchar_t *wcscat( wchar_t * restrict s1, const wchar_t * restrict s2 );
   // errno_t wcscat_s( wchar_t * restrict s1, rsize_t s1max,
   //                   const wchar_t * restrict s2);
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    wchar_t  lastname[32];
    wchar_t  firstname[32];
    _Bool    ismale;
} Name;

int main()
{
    Name *newName = calloc( 1, sizeof(Name) );

    /* ... check for calloc failure; read in the name parts ... */
    if( newName == NULL)
    {  fprintf( stderr, "Out of memory\n" ); return -1; }
    *newName = (Name) { L"Lincoln", L"Abraham", 1 };

    // Then display the new name
    wchar_t displayname[80];
    wcscpy( displayname, ( newName->ismale ? L"Mr. " : L"Ms. " ) );
    wcscat( displayname, newName->firstname );
    wcscat( displayname, L" " );
    wcscat( displayname, newName->lastname );
    wcscat( displayname, L"\n" );

    // Better to use wcscat_s() in case the fields in the Name
    // structure are ever enlarged:
    // wcscat_s( displayname, sizeof(displayname), newName->firstname );
    // wcscat_s( displayname, sizeof(displayname), L" " );
    // wcscat_s( displayname, sizeof(displayname), newName->lastname );
    // wcscat_s( displayname, sizeof(displayname), L"\n" );

    fputws( displayname, stdout );

    return 0;
}
