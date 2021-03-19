
#include "sqlite3.h"
#include <stdlib.h>

int main( int argc, char **argv )
{
    char            *file = ""; /* default to temp db */
    sqlite3         *db = NULL;
    sqlite3_stmt    *stmt = NULL;
    int             rc = 0;

    if ( argc > 1 )
        file = argv[1];

    sqlite3_initialize( );
    rc = sqlite3_open_v2( file, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );
    if ( rc != SQLITE_OK) {
        sqlite3_close( db );
        exit( -1 );
    }


    rc = sqlite3_prepare_v2( db, "CREATE TABLE tbl ( str TEXT )", -1, &stmt, NULL );
    if ( rc != SQLITE_OK) exit( -1 );

    rc = sqlite3_step( stmt );
    if ( rc != SQLITE_DONE ) exit ( -1 );
    
    sqlite3_finalize( stmt );



    sqlite3_close( db );
    sqlite3_shutdown( );
}

