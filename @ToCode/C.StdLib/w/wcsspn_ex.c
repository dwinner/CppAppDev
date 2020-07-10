// wcsspn_ex.c : wcsspn() example
// -------------------------------------------------------------

#include <wchar.h>     // size_t wcsspn( const wchar_t *s1,
                       //                const wchar_t *s2 );
#include <stdio.h>

int main()
{
    wchar_t wordin[256];
    double val;

    fputws( L"Enter a floating-point number, please: ", stdout );
    wscanf( L"%ls", wordin );

    int index = wcsspn( wordin, L"+-0123456789eE." );
    if ( index < wcslen( wordin ) )
       wprintf ( L"Sorry, but the character %lc is not permitted.\n",
                 wordin[index] );
    else
    {
       swscanf( wordin, L"%lg", &val );
       wprintf( L"You entered the value %g\n", val );
    }

    return 0;
}
