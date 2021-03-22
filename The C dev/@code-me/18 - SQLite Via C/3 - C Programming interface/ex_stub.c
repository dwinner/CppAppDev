
#include "sqlite3.h"
#include <stdlib.h>

int main( int argc, char **argv )
{
    char            *file = ""; /* default to temp db */
    sqlite3         *db = NULL;
    int             rc = 0;

    if ( argc > 1 )
        file = argv[1];

    sqlite3_initialize( );
    rc = sqlite3_open_v2( file, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );
    if ( rc != SQLITE_OK) {
        sqlite3_close( db );
        exit( -1 );
    }

    /*  perform database operations  */

    sqlite3_close( db );
    sqlite3_shutdown( );
}

