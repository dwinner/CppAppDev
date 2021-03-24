
#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char **argv )
{
    char            *file = ""; /* default to temp db */
    const char      *data = NULL;
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


    rc = sqlite3_prepare_v2( db, "SELECT str FROM tbl ORDER BY 1", -1, &stmt, NULL );
    if ( rc != SQLITE_OK) exit( -1 );

    while( sqlite3_step( stmt ) == SQLITE_ROW ) {
        data = (const char*)sqlite3_column_text( stmt, 0 );
        printf( "%s\n", data ? data : "[NULL]" );
    }
    
    sqlite3_finalize( stmt );



    sqlite3_close( db );
    sqlite3_shutdown( );
}

