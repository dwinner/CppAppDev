
#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const static char *weblog_sql = 
"    CREATE TABLE weblog (           "
"        ip_str       TEXT,          "  /*  0 */
"        login        TEXT HIDDEN,   "  /*  1 */
"        user         TEXT,          "  /*  2 */
"        time_str     TEXT,          "  /*  3 */
"        req          TEXT,          "  /*  4 */
"        result       INTEGER,       "  /*  5 */
"        bytes        INTEGER,       "  /*  6 */
"        ref          TEXT,          "  /*  7 */
"        agent        TEXT,          "  /*  8 */
#define TABLE_COLS_SCAN                9
"        ip_int       INTEGER,       "  /*  9 */
"        time_day     INTEGER,       "  /* 10 */
"        time_mon_s   TEXT,          "  /* 11 */
"        time_mon     INTEGER,       "  /* 12 */
"        time_year    INTEGER,       "  /* 13 */
"        time_hour    INTEGER,       "  /* 14 */
"        time_min     INTEGER,       "  /* 15 */
"        time_sec     INTEGER,       "  /* 16 */
"        req_op       TEXT,          "  /* 17 */
"        req_url      TEXT,          "  /* 18 */
"        line         TEXT HIDDEN    "  /* 19 */
"     );                             ";
#define TABLE_COLS                    20


typedef struct weblog_vtab_s {
    sqlite3_vtab   vtab;
    sqlite3        *db;
    char           *filename;
} weblog_vtab;


#define LINESIZE 4096

typedef struct weblog_cursor_s {
    sqlite3_vtab_cursor   cur;               /* this must be first */

    FILE           *fptr;                    /* used to scan file */
    sqlite_int64   row;                      /* current row count (ROWID) */
    int            eof;                      /* EOF flag */

    /* per-line info */
    char           line[LINESIZE];           /* line buffer */
    int            line_len;                 /* length of data in buffer */
    int            line_ptrs_valid;          /* flag for scan data */
    char           *(line_ptrs[TABLE_COLS]); /* array of pointers */
    int            line_size[TABLE_COLS];    /* length of data for each pointer */
} weblog_cursor;


static int weblog_get_line( weblog_cursor *c )
{
    char   *cptr;
    int    rc = SQLITE_OK;

    c->row++;                          /* advance row (line) counter */
    c->line_ptrs_valid = 0;            /* reset scan flag */
    cptr = fgets( c->line, LINESIZE, c->fptr );
    if ( cptr == NULL ) {  /* found the end of the file/error */
        if ( feof( c->fptr ) ) {
            c->eof = 1;
        } else {
            rc = -1;
        }
        return rc;
    }
    /* find end of buffer and make sure it is the end a line... */
    cptr = c->line + strlen( c->line ) - 1;       /* find end of string */
    if ( ( *cptr != '\n' )&&( *cptr != '\r' ) ) { /* overflow? */
        char   buf[1024], *bufptr;
        /* ... if so, keep reading */
        while ( 1 ) {
            bufptr = fgets( buf, sizeof( buf ), c->fptr );
            if ( bufptr == NULL ) {  /* found the end of the file/error */
                if ( feof( c->fptr ) ) {
                    c->eof = 1;
                } else {
                    rc = -1;
                }
                break;
            }
            bufptr = &buf[ strlen( buf ) - 1 ];
            if ( ( *bufptr == '\n' )||( *bufptr == '\r' ) ) {
                break;               /* found the end of this line */
            }
        }
    }

    while ( ( *cptr == '\n' )||( *cptr == '\r' ) ) {
        *cptr-- = '\0';   /* trim new-line characters off end of line */
    }
    c->line_len = ( cptr - c->line ) + 1;
    return rc;
}

static int weblog_scanline( weblog_cursor *c )
{
    char   *start = c->line, *end = NULL, next = ' ';
    int    i;

    /* clear pointers */
    for ( i = 0; i < TABLE_COLS; i++ ) {
        c->line_ptrs[i] = NULL;
        c->line_size[i] = -1;
    }

    /* process actual fields */
    for ( i = 0; i < TABLE_COLS_SCAN; i++ ) {
        next = ' ';
        while ( *start == ' ' )  start++;     /* trim whitespace */
        if (*start == '\0' )  break;          /* found the end */
        if (*start == '"' ) {
            next = '"';  /* if we started with a quote, end with one */
	    start++;
        }
        else if (*start == '[' ) {
            next = ']';  /* if we started with a bracket, end with one */
            start++;
        }
        end = strchr( start, next );    /* find end of this field */
        if ( end == NULL ) {            /* found the end of the line */
            int     len = strlen ( start );
            end = start + len;          /* end now points to '\0' */
        }
        c->line_ptrs[i] = start;        /* record start */
        c->line_size[i] = end - start;  /* record length */
        while ( ( *end != ' ' )&&( *end != '\0' ) )  end++;  /* find end */
        start = end;
    }

    /* process special fields */

    /* ip_int - just copy */
    c->line_ptrs[9] = c->line_ptrs[0];
    c->line_size[9] = c->line_size[0];

    /* assumes: "DD/MMM/YYYY:HH:MM:SS zone" */
    /*     idx:  012345678901234567890...   */
    if (( c->line_ptrs[3] != NULL )&&( c->line_size[3] >= 20 )) {
        start = c->line_ptrs[3];
        c->line_ptrs[10] = &start[0];    c->line_size[10] = 2;
        c->line_ptrs[11] = &start[3];    c->line_size[11] = 3;
        c->line_ptrs[12] = &start[3];    c->line_size[12] = 3;
        c->line_ptrs[13] = &start[7];    c->line_size[13] = 4;
        c->line_ptrs[14] = &start[12];   c->line_size[14] = 2;
        c->line_ptrs[15] = &start[15];   c->line_size[15] = 2;
        c->line_ptrs[16] = &start[18];   c->line_size[16] = 2;
    }

    /* req_op, req_url */
    start = c->line_ptrs[4];
    end = ( start == NULL ? NULL : strchr( start, ' ' ) );
    if ( end != NULL ) {
        c->line_ptrs[17] = start;
        c->line_size[17] = end - start;
        start = end + 1;
    }
    end = ( start == NULL ? NULL : strchr( start, ' ' ) );
    if ( end != NULL ) {
        c->line_ptrs[18] = start;
        c->line_size[18] = end - start;
    }

    /* line */
    c->line_ptrs[19] = c->line;
    c->line_size[19] = c->line_len;

    c->line_ptrs_valid = 1;
    return SQLITE_OK;
}


static int weblog_connect( sqlite3 *db, void *udp, int argc, 
        const char *const *argv, sqlite3_vtab **vtab, char **errmsg )
{
    weblog_vtab  *v = NULL;
    const char   *filename = argv[3];
    FILE         *ftest;

    if ( argc != 4 ) return SQLITE_ERROR;

    *vtab = NULL;
    *errmsg = NULL;

    /* test to see if filename is valid */
    ftest = fopen( filename, "r" );
    if ( ftest == NULL ) return SQLITE_ERROR;
    fclose( ftest );

    /* alloccate structure and set data */
    v = sqlite3_malloc( sizeof( weblog_vtab ) );
    if ( v == NULL ) return SQLITE_NOMEM;
    ((sqlite3_vtab*)v)->zErrMsg = NULL; /* need to init this */

    v->filename = sqlite3_mprintf( "%s", filename );
    if ( v->filename == NULL ) {
        sqlite3_free( v );
        return SQLITE_NOMEM;
    }
    v->db = db;

    sqlite3_declare_vtab( db, weblog_sql );
    *vtab = (sqlite3_vtab*)v;
    return SQLITE_OK;
}

static int weblog_disconnect( sqlite3_vtab *vtab )
{
    sqlite3_free( ((weblog_vtab*)vtab)->filename );
    sqlite3_free( vtab );
    return SQLITE_OK;
}

static int weblog_bestindex( sqlite3_vtab *vtab, sqlite3_index_info *info )
{
    return SQLITE_OK;
}

static int weblog_open( sqlite3_vtab *vtab, sqlite3_vtab_cursor **cur )
{
    weblog_vtab     *v = (weblog_vtab*)vtab;
    weblog_cursor   *c;
    FILE            *fptr;

    *cur = NULL;

    fptr = fopen( v->filename, "r" );
    if ( fptr == NULL ) return SQLITE_ERROR;

    c = sqlite3_malloc( sizeof( weblog_cursor ) );
    if ( c == NULL ) {
        fclose( fptr );
        return SQLITE_NOMEM;
    }
    
    c->fptr = fptr;
    *cur = (sqlite3_vtab_cursor*)c;
    return SQLITE_OK;
}

static int weblog_close( sqlite3_vtab_cursor *cur )
{
    if ( ((weblog_cursor*)cur)->fptr != NULL ) {
        fclose( ((weblog_cursor*)cur)->fptr );
    }
    sqlite3_free( cur );
    return SQLITE_OK;
}

static int weblog_filter( sqlite3_vtab_cursor *cur,
        int idxnum, const char *idxstr,
        int argc, sqlite3_value **value )
{
    weblog_cursor   *c = (weblog_cursor*)cur;

    fseek( c->fptr, 0, SEEK_SET );
    c->row = 0;
    c->eof = 0;
    return weblog_get_line( (weblog_cursor*)cur );
}

static int weblog_next( sqlite3_vtab_cursor *cur )
{
    return weblog_get_line( (weblog_cursor*)cur );
}

static int weblog_eof( sqlite3_vtab_cursor *cur )
{
    return ((weblog_cursor*)cur)->eof;
}

static int weblog_rowid( sqlite3_vtab_cursor *cur, sqlite3_int64 *rowid )
{
    *rowid = ((weblog_cursor*)cur)->row;
    return SQLITE_OK;
}

static int weblog_column( sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int cidx )
{
    weblog_cursor    *c = (weblog_cursor*)cur;

    if ( c->line_ptrs_valid == 0 ) {
        weblog_scanline( c );         /* scan line, if required */
    }
    if ( c->line_size[cidx] < 0 ) {   /* field not scanned and set */
        sqlite3_result_null( ctx );
        return SQLITE_OK;
    }

    switch( cidx ) {
    case 9: { /* convert IP address string to signed 64 bit integer */
        int            i;
        sqlite_int64   v = 0;
        char          *start = c->line_ptrs[cidx], *end, *oct[4];

        for ( i = 0; i < 4; i++ ) {
            oct[i] = start;
            end = ( start == NULL ? NULL : strchr( start, '.' ) );
            if ( end != NULL ) {
                start = end + 1;
            }
        }
        v += ( oct[3] == NULL ? 0 : atoi( oct[3] ) ); v *= 256;
        v += ( oct[2] == NULL ? 0 : atoi( oct[2] ) ); v *= 256;
        v += ( oct[1] == NULL ? 0 : atoi( oct[1] ) ); v *= 256;
        v += ( oct[0] == NULL ? 0 : atoi( oct[0] ) );
        sqlite3_result_int64( ctx, v );
        return SQLITE_OK;
    }
    case 12: { 
        int m = 0;
             if ( strncmp( c->line_ptrs[cidx], "Jan", 3 ) == 0 ) m =  1;
        else if ( strncmp( c->line_ptrs[cidx], "Feb", 3 ) == 0 ) m =  2;
        else if ( strncmp( c->line_ptrs[cidx], "Mar", 3 ) == 0 ) m =  3;
        else if ( strncmp( c->line_ptrs[cidx], "Apr", 3 ) == 0 ) m =  4;
        else if ( strncmp( c->line_ptrs[cidx], "May", 3 ) == 0 ) m =  5;
        else if ( strncmp( c->line_ptrs[cidx], "Jun", 3 ) == 0 ) m =  6;
        else if ( strncmp( c->line_ptrs[cidx], "Jul", 3 ) == 0 ) m =  7;
        else if ( strncmp( c->line_ptrs[cidx], "Aug", 3 ) == 0 ) m =  8;
        else if ( strncmp( c->line_ptrs[cidx], "Sep", 3 ) == 0 ) m =  9;
        else if ( strncmp( c->line_ptrs[cidx], "Oct", 3 ) == 0 ) m = 10;
        else if ( strncmp( c->line_ptrs[cidx], "Nov", 3 ) == 0 ) m = 11;
        else if ( strncmp( c->line_ptrs[cidx], "Dec", 3 ) == 0 ) m = 12;
        else break;    /* give up, return text */
        sqlite3_result_int( ctx, m );
        return SQLITE_OK;
    }
    case 5:    /* result code */
    case 6:    /* bytes transfered */
    case 10:   /* day-of-month */
    case 13:   /* year */
    case 14:   /* hour */
    case 15:   /* minute */
    case 16:   /* second */
        sqlite3_result_int( ctx, atoi( c->line_ptrs[cidx] ) );
        return SQLITE_OK;
    default:
        break;
    }
    sqlite3_result_text( ctx, c->line_ptrs[cidx],
                              c->line_size[cidx], SQLITE_STATIC );
    return SQLITE_OK;
}

static int weblog_rename( sqlite3_vtab *vtab, const char *newname )
{
    return SQLITE_OK;
}


static sqlite3_module weblog_mod = {
    1,                   /* iVersion        */
    weblog_connect,      /* xCreate()       */
    weblog_connect,      /* xConnect()      */
    weblog_bestindex,    /* xBestIndex()    */
    weblog_disconnect,   /* xDisconnect()   */
    weblog_disconnect,   /* xDestroy()      */
    weblog_open,         /* xOpen()         */
    weblog_close,        /* xClose()        */
    weblog_filter,       /* xFilter()       */
    weblog_next,         /* xNext()         */
    weblog_eof,          /* xEof()          */
    weblog_column,       /* xColumn()       */
    weblog_rowid,        /* xRowid()        */
    NULL,                /* xUpdate()       */
    NULL,                /* xBegin()        */
    NULL,                /* xSync()         */
    NULL,                /* xCommit()       */
    NULL,                /* xRollback()     */
    NULL,                /* xFindFunction() */
    weblog_rename        /* xRename()       */
};

int weblog_init( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);
    return sqlite3_create_module( db, "weblog", &weblog_mod, NULL );
}
