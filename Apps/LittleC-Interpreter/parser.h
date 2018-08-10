#ifndef LITTLEC_INTERPRETER_PARSER_H
#define LITTLEC_INTERPRETER_PARSER_H

#define _CRT_SECURE_NO_WARNINGS

#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_FUNC           100
#define NUM_GLOBAL_VARS    100
#define NUM_LOCAL_VARS     200
#define ID_LEN             32
#define FUNC_CALLS         31
#define PROG_SIZE          10000
#define FOR_NEST           31

/**
 * Token types
 */
enum tokTypes
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
   SWITCH,
   RETURN,
   CONTINUE,
   BREAK,
   EOL,
   FINISHED,
   END
};

/**
 * Operations with 2 operands
 */
enum doubleOps
{
   LT = 1,
   LE,
   GT,
   GE,
   EQ,
   NE
};

/**
 * These are the constants used to call sntxErr() when
 * a syntax error occurs. Add more if you like.
 * NOTE: Syntax is a generic error message used when
 * nothing else seems appropriate.
 */
enum errorMsg
{
   SYNTAX,
   UNBAL_PARENS,
   NO_EXP,
   EQUALS_EXPECTED,
   NOT_VAR,
   PARAM_ERR,
   SEMI_EXPECTED,
   UNBAL_BRACES,
   FUNC_UNDEF,
   TYPE_EXPECTED,
   NEST_FUNC,
   RET_NOCALL,
   PAREN_EXPECTED,
   WHILE_EXPECTED,
   QUOTE_EXPECTED,
   NOT_TEMP,
   TOO_MANY_LVARS,
   DIV_BY_ZERO
};

/**
 * Current location in source code
 */
extern char *prog;

/**
 * Points to start of program buffer
 */
extern char *p_buf;

/**
 * Hold environment for longjmp()
 */
extern jmp_buf e_buf;

/**
 * An array of these structures will hold the
 * info associated with global variables.
 */
extern struct var_type
{
   char var_name[ID_LEN];
   int v_type;
   int value;
} global_vars[NUM_GLOBAL_VARS];

/**
 * Function call stack
 */
extern struct func_type
{
   char func_name[ID_LEN];
   int ret_type;
   char *loc;  /* location in function entry point in file */
} func_stack[NUM_FUNC];

#endif //LITTLEC_INTERPRETER_PARSER_H
