// fscanf_ex.c : fscanf() example
//
// The example code reads information about a user from a file, which we will
// suppose contains a line of colon-separated strings like this:
//    tony:x:1002:31:Tony Crawford,,:/home/tony:/bin/bash// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1   // for fscanf_s()
#include <stdio.h> 
// int fscanf( FILE * restrict fp, const char * restrict format, ... );
// int fscanf_s( FILE * restrict fp, const char * restrict format, ... ); 

#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct pwrecord {             // Structure for contents of passwd fields.
    unsigned int uid;
    unsigned int gid;
    char user[32];
    char pw [32];
    char realname[128];
    char home [128];
    char shell [128];
};

int main()
{
    FILE *fp;
    char pwfile[] = "pwfile.txt";
    int results = 0;
    struct pwrecord record, *recptr = &record;;
    char gecos[256] = "";

    /* ... Open the password file to read ... */

    fp = fopen( pwfile, "r");
    if ( fp == NULL )
    {  perror( "Opening input file" ); return -1;  }

    /* 1. Read login name, password, UID and GID. */

    record = (struct pwrecord) { UINT_MAX, UINT_MAX, "", "", "", "", "" };
    results = fscanf( fp, "%31[^:]:%31[^:]:%u:%u:",
                      recptr->user, recptr->pw, &recptr->uid, &recptr->gid );

    // If the implementation supports the secure functions, the function fscanf_s()
    // can be used as an alternative to fscanf():
    /*
    results = fscanf_s( fp, "%31[^:]:%31[^:]:%u:%u:",
                        recptr->user, sizeof(recptr->user),
                        recptr->pw, sizeof(recptr->pw),
                        &recptr->uid, &recptr->gid );
    */
    if ( results < 4 )
    {
       fprintf( stderr, "Unable to parse line.\n" );
       fscanf( fp, "%*[^\n]\n" ); // Read and discard rest of line.
    }

    /* 2. Read the "gecos" field, which may contain nothing, or just the
     * real name, or comma-separated sub-fields.
    */
    results = fscanf( fp, "%255[^:]:", gecos );
    if ( results < 1 )
       strcpy( recptr->realname, "[No real name available]" );
    else
       sscanf( gecos, "%127[^,]", recptr->realname );    // Truncate at
                                                         // first comma.

    /* 3. Read two more fields before the end of the line. */

    results = fscanf( fp, "%127[^:]:%127[^:\n]\n", recptr->home, recptr->shell );
    if ( results < 2 )
    {
        fprintf( stderr, "Unable to parse line.\n" );
        fscanf( fp, "%*[^\n]\n" );            // Read and discard rest of line.
    }
    printf( "The user account %s with UID %u belongs to %s.\n",
             recptr->user, recptr->uid, recptr->realname );

    return 0;
}
