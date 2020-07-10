// c16tomb_ex.c : c16tomb() example
// -------------------------------------------------------------

#include <uchar.h>     // size_t c16rtomb( char * restrict dst, 
                       //                  char16_t c16,
                       //                  mbstate_t * restrict ps );

#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

int main()
{
    char16_t c16Str[] = u"Grüße";
    char mbChar[MB_CUR_MAX];
    mbstate_t mbstate = {0};

    if( setlocale(LC_ALL, "en_US.UTF-8") == NULL)
        fputs("Unable to set the locale.\n", stderr);

    for( int i = 0; c16Str[i] != 0; ++i)
    {
        size_t nBytes = c16rtomb( mbChar, c16Str[i], &mbstate );
        printf("0x%04X %lc Multibyte: [", c16Str[i], c16Str[i]);
        for( size_t j=0; j < nBytes; ++j)
           printf(" 0x%02X", (unsigned char)mbChar[j]);
        puts(" ]");
    }
    return 0;
}
