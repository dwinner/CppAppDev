// strcat_ex.c : strcat(), strcat_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1   // for strcat_s()

#include <string.h>  // char *strcat( char * restrict s1, 
                     //               const char * restrict s2 );
                     // errno_t strcat_s( char * restrict s1, rsize_t s1max,
                     //                   const char * restrict s2 );
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char  lastname[32];
    char  firstname[32];
    _Bool ismale;
} Name;

int main()
{
    char displayname[80];
    Name *newName = calloc( 1, sizeof(Name) );

    /* ... check for calloc failure; read in the name parts ... */
    if( newName == NULL)
    {  fprintf( stderr, "Out of memory\n" ); return -1; }
    *newName = (Name) { "Lincoln", "Abraham", 1 };

    strcpy( displayname, ( newName->ismale ? "Mr. " : "Ms. " ) );

    strcat( displayname, newName->firstname );
    strcat( displayname, " " );
    strcat( displayname, newName->lastname );

    // Better to use strcat_s() in case the fields in the Name
    // structure are ever enlarged:
    // strcat_s( displayname, sizeof(displayname), newName->firstname );
    // strcat_s( displayname, sizeof(displayname), " " );
    // strcat_s( displayname, sizeof(displayname), newName->lastname );

    puts( displayname );

    return 0;
}
