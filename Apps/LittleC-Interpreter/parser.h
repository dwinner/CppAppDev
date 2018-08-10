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

#endif //LITTLEC_INTERPRETER_PARSER_H
