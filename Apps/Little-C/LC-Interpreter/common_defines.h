#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

#define NUM_FUNC           100
#define NUM_GLOBAL_VARS    100
#define NUM_LOCAL_VARS     200
#define ID_LEN             32
#define PROG_SIZE          10000
#define NUM_PARAMS         31

/**
 * Tokens
 */
enum tokens
{
   ARG,
   CHAR,
   INT,
   IF,
   ELSE,
   FOR,
   DO,
   WHILE,
   RETURN,
   CONTINUE,
   BREAK,
   FINISHED,
   END
};

/**
* Token types
*/
enum tok_types
{
   DELIMETER,
   IDENTIFIER,
   NUMBER,
   KEYWORD,
   TEMP,
   STRING,
   BLOCK
};

/**
* These are constants used to call sntxErr()
* when a syntax error occurs. Add more if you like.
* NOTE: SYNTAX is a generic error message used when
* nothing else seems appropriate.
*/
enum errorMsg
{
   SYNTAX,
   NO_EXP,
   NOT_VAR,
   SEMI_EXPECTED,
   FUNC_UNDEF,
   TYPE_EXPECTED,
   NEST_FUNC,
   RET_NOCALL,
   PAREN_EXPECTED,
   WHILE_EXPECTED,
   QUOTE_EXPECTED,
   TOO_MANY_LVARS,
   DIV_BY_ZERO
};

#endif // COMMON_DEFINES_H
