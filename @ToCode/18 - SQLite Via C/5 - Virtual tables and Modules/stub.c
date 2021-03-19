
#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
#include <stdio.h>

const static char *stub_sql = "CREATE TABLE t "
" ( a INTEGER, b INTEGER, c INTEGER, d INTEGER ); ";

typedef struct stub_vtab_s {
   sqlite3_vtab           vtab;
} stub_vtab;
typedef struct stub_cursor_s {
    sqlite3_vtab_cursor   cur;
    sqlite_int64          row;
} stub_cursor;



static int stub_create( sqlite3 *db, void *udp, int argc, 
        const char *const *argv, sqlite3_vtab **vtab, char **errmsg )
{
    int i;
    printf( "CREATE:\n" );
    for ( i=0; i < argc; i++ ) {
        printf( "   %2d: %s\n", i, argv[i] );
    }

    stub_vtab     *v = NULL;

    v = sqlite3_malloc( sizeof( stub_vtab ) );

    if ( v == NULL ) return SQLITE_NOMEM;
    v->vtab.zErrMsg = NULL;

    sqlite3_declare_vtab( db, stub_sql );
    *vtab = (sqlite3_vtab*)v;
    return SQLITE_OK;
}

static int stub_connect( sqlite3 *db, void *udp, int argc, 
        const char *const *argv, sqlite3_vtab **vtab, char **errmsg )
{
    int i;
    printf( "CONNECT:\n" );
    for ( i=0; i < argc; i++ ) {
        printf( "   %2d: %s\n", i, argv[i] );
    }

    stub_vtab     *v = NULL;

    v = sqlite3_malloc( sizeof( stub_vtab ) );

    if ( v == NULL ) return SQLITE_NOMEM;
    v->vtab.zErrMsg = NULL;

    sqlite3_declare_vtab( db, stub_sql );
    *vtab = (sqlite3_vtab*)v;
    return SQLITE_OK;
}

static int stub_disconnect( sqlite3_vtab *vtab )
{
    printf( "DISCONNECT\n" );

    sqlite3_free( vtab );
    return SQLITE_OK;
}

static int stub_destroy( sqlite3_vtab *vtab )
{
    printf( "DESTROY\n" );

    sqlite3_free( vtab );
    return SQLITE_OK;
}

static char* op( unsigned char op )
{
    if ( op == SQLITE_INDEX_CONSTRAINT_EQ ) return "=";
    if ( op == SQLITE_INDEX_CONSTRAINT_GT ) return ">";
    if ( op == SQLITE_INDEX_CONSTRAINT_LE ) return "<=";
    if ( op == SQLITE_INDEX_CONSTRAINT_LT ) return "<";
    if ( op == SQLITE_INDEX_CONSTRAINT_GE ) return ">=";
    if ( op == SQLITE_INDEX_CONSTRAINT_MATCH ) return "MATCH";
    return "?";
}

static int stub_bestindex( sqlite3_vtab *vtab, sqlite3_index_info *info )
{
    int i;
    printf( "BEST INDEX:\n" );
    for ( i=0; i < info->nConstraint; i++ ) {
        printf( "   CONST[%d]: %d %s %s\n", i, info->aConstraint[i].iColumn,
	            op( info->aConstraint[i].op ), 
		    info->aConstraint[i].usable ? "Usable" : "Unusable" );
    }
    for ( i=0; i < info->nOrderBy; i++ ) {
        printf( "   ORDER[%d]: %d %s\n", i, info->aOrderBy[i].iColumn,
	            info->aOrderBy[i].desc ? "DESC" : "ASC" );
    }

    return SQLITE_OK;
}

static int stub_open( sqlite3_vtab *vtab, sqlite3_vtab_cursor **cur )
{
    stub_vtab     *v = (stub_vtab*)vtab;
    stub_cursor   *c;

    printf( "OPEN\n" );

    c = sqlite3_malloc( sizeof( stub_cursor ) );
    if ( c == NULL ) return SQLITE_NOMEM;

    *cur = (sqlite3_vtab_cursor*)c;
    c->row = 0;
    return SQLITE_OK;
}

static int stub_close( sqlite3_vtab_cursor *cur )
{
    printf( "CLOSE\n" );

    sqlite3_free( cur );
    return SQLITE_OK;
}

static int stub_filter( sqlite3_vtab_cursor *cur,
        int idxnum, const char *idxstr,
        int argc, sqlite3_value **value )
{
    printf( "FILTER\n" );

    return SQLITE_OK;
}

static int stub_next( sqlite3_vtab_cursor *cur )
{
    printf( "NEXT\n" );

    ((stub_cursor*)cur)->row++;
    return SQLITE_OK;
}

static int stub_eof( sqlite3_vtab_cursor *cur )
{
    printf( "EOF\n" );

    return ( ((stub_cursor*)cur)->row >= 10 );
}

static int stub_rowid( sqlite3_vtab_cursor *cur, sqlite3_int64 *rowid )
{
    printf( "ROWID: %lld\n", ((stub_cursor*)cur)->row );

    *rowid = ((stub_cursor*)cur)->row;
    return SQLITE_OK;
}

static int stub_column( sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int cidx )
{
    stub_cursor    *c = (stub_cursor*)cur;

    printf( "COLUMN: %d\n", cidx );

    sqlite3_result_int( ctx, c->row * 10 + cidx );
    return SQLITE_OK;
}

static int stub_rename( sqlite3_vtab *vtab, const char *newname )
{
    printf( "RENAME\n" );

    return SQLITE_OK;
}

static int stub_update( sqlite3_vtab *vtab, int argc, sqlite3_value **argv, sqlite_int64 *rowid )
{
	printf( "UPDATE: " );

	if ( argc == 1 ) {
	    printf( "DELETE %d\n", sqlite3_value_int( argv[0] ) );
	    
	    return SQLITE_OK;
	}

        if ( sqlite3_value_type( argv[0] ) == SQLITE_NULL ) {
            if ( sqlite3_value_type( argv[1] ) == SQLITE_NULL ) {
                printf( "INSERT -\n" );

		*rowid = 10;
	    }
	    else {
	        printf( "INSERT %d\n", sqlite3_value_int( argv[1] ) );
	    }
	    return SQLITE_OK;
	}

	printf( "UPDATE %d %d\n", sqlite3_value_int( argv[0] ), sqlite3_value_int( argv[1] ) );
	return SQLITE_OK;
}

static int stub_begin( sqlite3_vtab *vtab )
{
    printf( "BEGIN\n" );

    return SQLITE_OK;
}

static int stub_sync( sqlite3_vtab *vtab )
{
    printf( "SYNC\n" );

    return SQLITE_OK;
}

static int stub_commit( sqlite3_vtab *vtab )
{
    printf( "COMMIT\n" );

    return SQLITE_OK;
}

static int stub_rollback( sqlite3_vtab *vtab )
{
    printf( "ROLLBACK\n" );

    return SQLITE_OK;
}



static sqlite3_module stub_mod = {
    1,                 /* iVersion        */
    stub_create,       /* xCreate()       */
    stub_connect,      /* xConnect()      */
    stub_bestindex,    /* xBestIndex()    */
    stub_disconnect,   /* xDisconnect()   */
    stub_destroy,      /* xDestroy()      */
    stub_open,         /* xOpen()         */
    stub_close,        /* xClose()        */
    stub_filter,       /* xFilter()       */
    stub_next,         /* xNext()         */
    stub_eof,          /* xEof()          */
    stub_column,       /* xColumn()       */
    stub_rowid,        /* xRowid()        */
    stub_update,       /* xUpdate()       */
    stub_begin,        /* xBegin()        */
    stub_sync,         /* xSync()         */
    stub_commit,       /* xCommit()       */
    stub_rollback,     /* xRollback()     */
    NULL,              /* xFindFunction() */
    stub_rename        /* xRename()       */
};

int stub_init( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);
    return sqlite3_create_module( db, "stub", &stub_mod, NULL );
}


