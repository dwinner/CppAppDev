// strpbrk_ex.c : strpbrk() example
// -------------------------------------------------------------

#include <string.h>    // char *strpbrk( const char *s1, 
                       //                const char *s2 );
#include <stdio.h>

int main()
{
    char *story = "He shouted: \"What? I can't hear you!\"\n";
    char separators[] = " \t\n.:?!\"";
    char *start = story, *end = NULL;
    char words[16][16];     // An array of char arrays to collect words in.
    int i = 0;

    while ( i < 16 && ( end = strpbrk( start, separators ) ) != NULL )
    {
      if ( end != start )   // If the separator wasn't the first character,
      {                     // then save a word in an array.
         strncpy( words[i], start, end - start );
         words[i][end - start] = '\0';     // And terminate it.
         i++;
      }
      start = end + 1;      // Next strpbrk call starts with
    }                       // the character after this separator.

    puts( story );

    for ( int j = 0 ; j < i ; j++ )
       puts( words[j] );

    return 0;
}
