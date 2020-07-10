// wcspbrk_ex.c : wcspbrk() example
// -------------------------------------------------------------

#include <wchar.h>     // wchar_t *wcspbrk( const wchar_t *s1,
                       //                   const wchar_t *s2 );
#include <stdio.h>

int main()
{
    wchar_t *story = L"He shouted: \"What? I can't hear you!\"\n";
    wchar_t separators[ ] = L" \t\n.:?!\"";
    wchar_t *start = story, *end = NULL;
    wchar_t words[16][16];   // An array of wchar_t arrays to collect words in. 
    int i = 0;

    while ( i < 16 && ( end = wcspbrk( start, separators ) ) != NULL )
    {
      if ( end != start )             // If the separator wasn't the first
      {                               // character in the substring,
         wcsncpy( words[i], start, end - start );  // then save a word.
         words[i][end - start] = L'\0';            // And terminate it.
         i++;
      }
      start = end + 1;                // Next wcspbrk call starts with the
    }                                 // character after this separator.

    fputws( story, stdout );

    for ( int j = 0 ; j < i ; j++ )
    {
       fputws( words[j], stdout );
       fputwc( L'\n', stdout );
    }

    return 0;
}
