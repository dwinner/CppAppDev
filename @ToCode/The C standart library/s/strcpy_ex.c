// strcpy_ex.c : strcpy(), strcpy_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1   // for strcpy_s()

#include <string.h>  // char *strcpy( char * restrict dest,
                     //               const char * restrict src );
                     // errno_t strcpy_s( char * restrict dest, 
                     //                   rsize_t destmax,
                     //                   const char * restrict src );
#include <stdio.h>

int main()
{
    struct guest {
       char name[64]; int age; _Bool male, smoking, discount; } this;
    int result;

    printf( "Last name: " );
    result = scanf( "%[^\n]", this.name );
    if ( result < 1 )
       strcpy( this.name, "[not available]" );
   // or
   // strcpy_s( this.name, sizeof(this.name), "[not available]" );

    printf( "Name: %s\n", this.name );

    return 0;
}
