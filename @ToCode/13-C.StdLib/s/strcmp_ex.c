// strcmp_ex.c : strcmp() example
// -------------------------------------------------------------

#include <string.h>  // int strcmp( const char *s1, const char *s2);
#include <stdio.h>

int main()
{
    int result = 0;
    char word1[256], word2[256], *greaterlessequal;

    while ( result < 2 )
    {
        puts( "Type two words, please." );
        result = scanf( "%s%s", word1, word2 );
    }
    result = strcmp( word1, word2 );

    if ( result < 0 )
       greaterlessequal = "less than";
    else if ( result > 0 )
       greaterlessequal = "greater than";
    else
       greaterlessequal = "the same as";

    printf( "The word \"%s\" is %s the word \"%s\".\n",
            word1, greaterlessequal, word2 );

    return 0;
}
