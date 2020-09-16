// iswalpha_ex.c : iswalpha() example
// And also an example for
// iswalnum(), iswblank(), iswcntrl(), iswdigit(), iswgraph(),
// iswlower(), iswprint(), iswpunct(), iswspace().
// -------------------------------------------------------------

#include <wctype.h>    // int iswalpha( wint_t wc);  ...
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
    wint_t wc;

    if ( setlocale( LC_CTYPE, "" ) == NULL)
    {
       fwprintf( stderr,
                 L"Sorry, couldn't change to the system's native locale.\n");
       return 1;
    }
    wprintf( L"The current locale for the 'isw ...' functions is '%s'.\n",
             setlocale(LC_CTYPE, NULL));

    wprintf( L"Here is a table of the 'isw ...' values for the characters "
             L"from 128 to 255 in this locale:\n\n");

    for ( wc = 128; wc < 255; ++wc ) // Loop iteration for each table row.
    {
       if ( (wc-128) % 24 == 0 ) // Repeat table header every 24 rows.
       {
         wprintf(L"Code char alnum alpha blank cntrl digit graph lower"
                 L" print punct space\n");
         wprintf(L"---------------------------------------------------"
                 L"------------------\n");
       }
       wprintf(L"%4u %4lc %3c %5c %5c %5c %5c %5c %5c %5c %5c %5c\n",
               wc,                              // Print numeric character code.
               ( iswprint( wc ) ? wc  : ' ' ),  // Print the glyph, or a space
                                                // if it's not printable.
               ( iswalnum( wc ) ? 'X' : '-' ),  // In a column for each
               ( iswalpha( wc ) ? 'X' : '-' ),  // category, print X for
               ( iswblank( wc ) ? 'X' : '-' ),  // yes or - for no.
               ( iswcntrl( wc ) ? 'X' : '-' ),
               ( iswdigit( wc ) ? 'X' : '-' ),
               ( iswgraph( wc ) ? 'X' : '-' ),
               ( iswlower( wc ) ? 'X' : '-' ),
               ( iswprint( wc ) ? 'X' : '-' ),
               ( iswpunct( wc ) ? 'X' : '-' ),
               ( iswspace( wc ) ? 'X' : '-' ) );
    } // end of loop for each character value

    return 0;
}
