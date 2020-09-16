// wcscmp_ex.c : wcscmp() example
// -------------------------------------------------------------

#include <wchar.h>   // int wcscmp( const wchar_t *s1, const wchar_t *s2 );
#include <stdio.h>

int main()
{
    int result = 0;
    wchar_t word1[255]=L"X1", word2[256] = L"X2", *greaterlessequal;

    while ( result < 2 )
    {
        fputws( L"Type two words, please: ", stdout );
        result = wscanf( L"%255ls %255ls", word1, word2 );
        if ( result == EOF )
           return EOF;
    }
    result = wcscmp( word1, word2 );

    if ( result < 0 )
       greaterlessequal = L"less than";
    else if ( result > 0 )
       greaterlessequal = L"greater than";
    else
       greaterlessequal = L"the same as";

    wprintf( L"The word \"%ls\" is %ls the word \"%ls\".\n", 
             word1, greaterlessequal, word2 );

    return 0;
}
