
#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char *dblist_sql = 
"CREATE TABLE dblist ( seq INTEGER, name TEXT, file TEXT );";

typedef struct dblist_vtab_s {
    sqlite3_vtab          vtab;  /* this must go first */
    sqlite3               *db;   /* module specific fields then follow */
} dblist_vtab;

typedef struct dblist_cursor_s {
    sqlite3_vtab_cursor   cur;    /* this must go first */
    sqlite3_stmt          *stmt;  /* PRAGMA database_list statement */
    int                   eof;    /* EOF flag */
} dblist_cursor;



static int dblist_get_row( dblist_cursor *c )
{
    int  rc;
    
    if ( c->eof ) return SQLITE_OK;
    rc = sqlite3_step( c->stmt );
    if ( rc == SQLITE_ROW ) return SQLITE_OK;     /* we have a valid row */

    sqlite3_reset( c->stmt );
    c->eof = 1;
    return ( rc == SQLITE_DONE ? SQLITE_OK : rc );  /* DONE -> OK */
}

static int dblist_connect( sqlite3 *db, void *udp, int argc, 
        const char *const *argv, sqlite3_vtab **vtab, char **errmsg )
{
    dblist_vtab    *v = NULL;

    *vtab = NULL;
    *errmsg = NULL;
    if ( argc != 3 )  return SQLITE_ERROR;
    if ( sqlite3_declare_vtab( db, dblist_sql ) != SQLITE_OK ) {
        return SQLITE_ERROR;
    }

    v = sqlite3_malloc( sizeof( dblist_vtab ) ); /* alloc our custom vtab */
    *vtab = (sqlite3_vtab*)v;
    if ( v == NULL ) return SQLITE_NOMEM;

    v->db = db;                                  /* stash this for later */
    (*vtab)->zErrMsg = NULL;                     /* initalize this */
    return SQLITE_OK;
}

static int dblist_disconnect( sqlite3_vtab *vtab )
{
    sqlite3_free( vtab );
    return SQLITE_OK;
}

static int dblist_bestindex( sqlite3_vtab *vtab, sqlite3_index_info *info )
{
    return SQLITE_OK;
}

static int dblist_open( sqlite3_vtab *vtab, sqlite3_vtab_cursor **cur )
{
    dblist_vtab    *v = (dblist_vtab*)vtab;
    dblist_cursor  *c = NULL;
    int            rc = 0;

    c = sqlite3_malloc( sizeof( dblist_cursor ) );
    *cur = (sqlite3_vtab_cursor*)c;
    if ( c == NULL ) return SQLITE_NOMEM;

    rc = sqlite3_prepare_v2( v->db, "PRAGMA database_list", -1, &c->stmt, NULL );
    if ( rc != SQLITE_OK ) {
        *cur = NULL;
        sqlite3_free( c );
        return rc;
    }
    return SQLITE_OK;
}

static int dblist_close( sqlite3_vtab_cursor *cur )
{
    sqlite3_finalize( ((dblist_cursor*)cur)->stmt );
    sqlite3_free( cur );
    return SQLITE_OK;
}

static int dblist_filter( sqlite3_vtab_cursor *cur,
            int idxnum, const char *idxstr,
            int argc, sqlite3_value **value )
{
    dblist_cursor  *c = (dblist_cursor*)cur;
    int            rc = 0;

    rc = sqlite3_reset( c->stmt );     /* start a new scan */
    if ( rc != SQLITE_OK ) return rc;
    c->eof = 0;                        /* clear EOF flag */

    dblist_get_row( c );               /* fetch first row */
    return SQLITE_OK;
}

static int dblist_next( sqlite3_vtab_cursor *cur )
{
    return dblist_get_row( (dblist_cursor*)cur );
}

static int dblist_eof( sqlite3_vtab_cursor *cur )
{
    return ((dblist_cursor*)cur)->eof;
}

static int dblist_column( sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int cidx )
{
    dblist_cursor   *c = (dblist_cursor*)cur;
    sqlite3_result_value( ctx, sqlite3_column_value( c->stmt, cidx ) );
    return SQLITE_OK;
}

static int dblist_rowid( sqlite3_vtab_cursor *cur, sqlite3_int64 *rowid )
{
    *rowid = sqlite3_column_int64( ((dblist_cursor*)cur)->stmt, 0 );
    return SQLITE_OK;
}

static int dblist_rename( sqlite3_vtab *vtab, const char *newname )
{
    return SQLITE_OK;
}


static sqlite3_module dblist_mod = {
    1,                   /* iVersion        */
    dblist_connect,      /* xCreate()       */
    dblist_connect,      /* xConnect()      */
    dblist_bestindex,    /* xBestIndex()    */
    dblist_disconnect,   /* xDisconnect()   */
    dblist_disconnect,   /* xDestroy()      */
    dblist_open,         /* xOpen()         */
    dblist_close,        /* xClose()        */
    dblist_filter,       /* xFilter()       */
    dblist_next,         /* xNext()         */
    dblist_eof,          /* xEof()          */
    dblist_column,       /* xColumn()       */
    dblist_rowid,        /* xRowid()        */
    NULL,                /* xUpdate()       */
    NULL,                /* xBegin()        */
    NULL,                /* xSync()         */
    NULL,                /* xCommit()       */
    NULL,                /* xRollback()     */
    NULL,                /* xFindFunction() */
    dblist_rename        /* xRename()       */
};

int dblist_init( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    int   rc;

    SQLITE_EXTENSION_INIT2(api);

    /* register module */
    rc = sqlite3_create_module( db, "dblist", &dblist_mod, NULL );
    if ( rc != SQLITE_OK ) {
        return rc;
    }

    /* automatically create an instance of the virtual table */
    rc = sqlite3_exec( db, 
        "CREATE VIRTUAL TABLE temp.sql_database_list USING dblist", 
        NULL, NULL, NULL  );
    return rc;
}

