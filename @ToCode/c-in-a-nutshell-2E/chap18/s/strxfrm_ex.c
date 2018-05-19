// strxfrm_ex.c : strxfrm() example
// -------------------------------------------------------------

#include <string.h>  // size_t strxfrm( char * restrict dest,
                     //                 const char * restrict src,
                     //                 size_t n );
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct stringpair { char * original;
                            char * xformed; } Stringpair_t ;

Stringpair_t stringpairs[8] =
             { { "Chávez", NULL },        { "Carron", NULL },
               { "Canoso", NULL },        { "Cañoso", NULL },
               { "Carteño", NULL },       { "Cortillo", NULL },
               { "Cortiluz S.A.", NULL }, { "Corriando", NULL } };

char xformbuffer[1024];           // Space to catch each strxfrm() result.

int stringpaircmp( const void * p1, const void *p2 );
                                  // Defined externally.

int main()
{
    setlocale( LC_COLLATE, "");    // Use the host system's locale setting.
//    printf( "The locale is %s.\n", setlocale( LC_COLLATE, NULL) );

    for ( int i = 0; i < 8 ; i++ )
    {
        stringpairs[i].xformed
        = malloc( strxfrm( xformbuffer, stringpairs[i].original, 1024 ) + 1 );
        if ( stringpairs[i].xformed != NULL )
           strcpy(stringpairs[i].xformed, xformbuffer);
    }

    qsort( stringpairs, 8, sizeof(Stringpair_t), stringpaircmp );

    for ( int i = 0; i < 8 ; i++ )
        puts( stringpairs[i].original );

    return 0;
}

int stringpaircmp( const void * sp1, const void *sp2 )
{
    const char * s1 = ((Stringpair_t *)sp1)->xformed;
    const char * s2 = ((Stringpair_t *)sp2)->xformed;
    return strcmp( s1, s2 );
}
