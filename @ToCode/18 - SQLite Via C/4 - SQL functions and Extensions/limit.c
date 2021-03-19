
/* limit.c */

#include "sqlite3ext.h"
SQLITE_EXTENSION_INIT1;

#include <stdlib.h>


/* This file includes all the sql_limit() examples from
 * Chapter 9 of "Using SQLite" as a module.
 *
 * Included are the four functions:
 *
 *   sql_set_limit()
 *   sql_get_limit()
 *   sql_getset_limit()
 *   sql_getset_var_limit()
 *
 * Plus the helper function:
 *
 *   decode_limit_str()
 *
 * There are also several _init function that can be
 * used as the module entry point.  The function
 * limit_init() will bind the third example (sql_getset_limit())
 * to the SQL function sql_limit(), and then each example
 * set of code to sql_limit1(),... etc.
 * 
 * The init functions limit_init1(),... etc. will bind a
 * specific example to sql_limit().
 *
 */


/* This is the limit decode function used by all the other functions */
static int decode_limit_str( const char *str )
{
    if ( str == NULL ) return -1;    
    if ( !strcmp( str, "LENGTH"          ) ) return SQLITE_LIMIT_LENGTH;
    if ( !strcmp( str, "SQL_LENGTH"      ) ) return SQLITE_LIMIT_SQL_LENGTH;
    if ( !strcmp( str, "COLUMN"          ) ) return SQLITE_LIMIT_COLUMN;
    if ( !strcmp( str, "EXPR_DEPTH"      ) ) return SQLITE_LIMIT_EXPR_DEPTH;
    if ( !strcmp( str, "COMPOUND_SELECT" ) ) return SQLITE_LIMIT_COMPOUND_SELECT;
    if ( !strcmp( str, "VDBE_OP"         ) ) return SQLITE_LIMIT_VDBE_OP;
    if ( !strcmp( str, "FUNCTION_ARG"    ) ) return SQLITE_LIMIT_FUNCTION_ARG;
    if ( !strcmp( str, "ATTACHED"        ) ) return SQLITE_LIMIT_ATTACHED;
    if ( !strcmp( str, "LIKE_LENGTH"     ) ) return SQLITE_LIMIT_LIKE_PATTERN_LENGTH;
    if ( !strcmp( str, "VARIABLE_NUMBER" ) ) return SQLITE_LIMIT_VARIABLE_NUMBER;
    if ( !strcmp( str, "TRIGGER_DEPTH"   ) ) return SQLITE_LIMIT_TRIGGER_DEPTH;
    return -1;
}


/* Example 1: sql_set_limit() */
static void sql_set_limit( sqlite3_context *ctx, int num_values, sqlite3_value **values )
{
    sqlite3      *db = sqlite3_context_db_handle( ctx );
    const char   *str = NULL;
    int           limit = -1, val = -1, result = -1;

    /* verify the first param is a string and extract pointer */
    if ( sqlite3_value_type( values[0] ) == SQLITE_TEXT ) {
        str = (const char*) sqlite3_value_text( values[0] );
    } else {
        sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
        return;
    }

    /* verify the second parameter is an integer and extract value */
    if ( sqlite3_value_type( values[1] ) == SQLITE_INTEGER ) {
        val = sqlite3_value_int( values[1] );
    } else {
        sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
        return;
    }

    /* translate string into integer limit */
    limit = decode_limit_str( str );
    if ( limit == -1 ) {
        sqlite3_result_error( ctx, "sql_limit(): unknown limit type", -1 );
        return;
    }

    /* call sqlite3_limit(), return result */
    result = sqlite3_limit( db, limit, val );
    sqlite3_result_int( ctx, result );
    return;
}


/* Example 2: sql_get_limit(), used with sql_set_limit() */
static void sql_get_limit( sqlite3_context *ctx, int num_values, sqlite3_value **values )
{
    sqlite3      *db = sqlite3_context_db_handle( ctx );
    const char   *str = NULL;
    int           limit = -1, val = -1, result = -1;

    /* verify param types and extract values */
    if ( sqlite3_value_type( values[0] ) == SQLITE_TEXT ) {
        str = (const char*) sqlite3_value_text( values[0] );
    } else {
        sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
        return;
    }
    
    limit = decode_limit_str( str );
    if ( limit == -1 ) {
        sqlite3_result_error( ctx, "sql_limit(): unknown limit type", -1 );
        return;
    }

    /* call sqlite3_limit(), return result */
    result = sqlite3_limit( db, limit, val );
    sqlite3_result_int( ctx, result );
    return;
}


/* Example 3: sql_getset_limit() */
static void sql_getset_limit( sqlite3_context *ctx, int num_values, sqlite3_value **values )
{
    sqlite3      *db = sqlite3_context_db_handle( ctx );
    const char   *str = NULL;
    int           limit = -1, val = -1, result = -1;

    /* verify the first param is a string and extract pointer */
    if ( sqlite3_value_type( values[0] ) == SQLITE_TEXT ) {
        str = (const char*) sqlite3_value_text( values[0] );
    } else {
        sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
        return;
    }

    /* verify the second parameter is an integer and extract value */
    if ( num_values == 2 ) {
        if ( sqlite3_value_type( values[1] ) == SQLITE_INTEGER ) {
            val = sqlite3_value_int( values[1] );
        } else {
            sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
            return;
        }
    }

    /* translate string into integer limit */
    limit = decode_limit_str( str );
    if ( limit == -1 ) {
        sqlite3_result_error( ctx, "sql_limit(): unknown limit type", -1 );
        return;
    }

    /* call sqlite3_limit(), return result */
    result = sqlite3_limit( db, limit, val );
    sqlite3_result_int( ctx, result );
    return;
}


/* Example 4: sql_getset_var_limit() */
static void sql_getset_var_limit( sqlite3_context *ctx, int num_values, sqlite3_value **values )
{
    sqlite3      *db = sqlite3_context_db_handle( ctx );
    const char   *str = NULL;
    int           limit = -1, val = -1, result = -1;

    /* verify number of params */
    if ( ( num_values < 1 )||( num_values > 2 ) ) {
        sqlite3_result_error( ctx, "sql_limit(): bad parameter count", -1 );
        return;
    }

    /* verify param types and extract values */
    if ( sqlite3_value_type( values[0] ) == SQLITE_TEXT ) {
        str = (const char*) sqlite3_value_text( values[0] );
    } else {
        sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
        return;
    }

    if ( num_values == 2 ) {
        if ( sqlite3_value_type( values[1] ) == SQLITE_INTEGER ) {
            val = sqlite3_value_int( values[1] );
        } else {
            sqlite3_result_error( ctx, "sql_limit(): wrong parameter type", -1 );
            return;
        }
    }
    
    limit = decode_limit_str( str );
    if ( limit == -1 ) {
        sqlite3_result_error( ctx, "sql_limit(): unknown limit type", -1 );
        return;
    }

    /* call sqlite3_limit(), return result */
    result = sqlite3_limit( db, limit, val );
    sqlite3_result_int( ctx, result );
    return;
}


/*********************************************************/

/* Module entry-point functions */

/* Example 1: register just sql_set_limit() */
int limit_init1( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);

    sqlite3_create_function( db, "sql_limit", 2,
            SQLITE_UTF8, NULL, sql_set_limit, NULL, NULL );
    return SQLITE_OK;
}

/* Example 2: register sql_get_limit() and sql_set_limit() */
int limit_init2( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);

    sqlite3_create_function( db, "sql_limit", 1,
            SQLITE_UTF8, NULL, sql_get_limit, NULL, NULL );
    sqlite3_create_function( db, "sql_limit", 2,
            SQLITE_UTF8, NULL, sql_set_limit, NULL, NULL );
    return SQLITE_OK;
}

/* Example 3: register sql_getset_limit() */
int limit_init3( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);

    sqlite3_create_function( db, "sql_limit", 1,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );
    sqlite3_create_function( db, "sql_limit", 2,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );
    return SQLITE_OK;
}

/* Example 4: register sql_getset_var_limit()  */
int limit_init4( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);

    sqlite3_create_function( db, "sql_limit", -1,
            SQLITE_UTF8, NULL, sql_getset_var_limit, NULL, NULL );
    return SQLITE_OK;
}



/* Register all four examples under different names: */
int limit_init( sqlite3 *db, char **error, const sqlite3_api_routines *api )
{
    SQLITE_EXTENSION_INIT2(api);

    /* "standard" way to do things registered as sql_limit() */
    sqlite3_create_function( db, "sql_limit", 1,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );
    sqlite3_create_function( db, "sql_limit", 2,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );


    /* sql_set_limit() registered as sql_limit1() */
    sqlite3_create_function( db, "sql_limit1", 2,
            SQLITE_UTF8, NULL, sql_set_limit, NULL, NULL );

    /* sql_get_limit() and sql_set_limit() registered as sql_limit2() */
    sqlite3_create_function( db, "sql_limit2", 1,
            SQLITE_UTF8, NULL, sql_get_limit, NULL, NULL );
    sqlite3_create_function( db, "sql_limit2", 2,
            SQLITE_UTF8, NULL, sql_set_limit, NULL, NULL );

    /* sql_getset_limit() registered as sql_limit3() */
    sqlite3_create_function( db, "sql_limit3", 1,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );
    sqlite3_create_function( db, "sql_limit3", 2,
            SQLITE_UTF8, NULL, sql_getset_limit, NULL, NULL );

    /* sql_getset_var_limit() registered as sql_limit4() */
    sqlite3_create_function( db, "sql_limit4", -1,
            SQLITE_UTF8, NULL, sql_getset_var_limit, NULL, NULL );

    return SQLITE_OK;
}

