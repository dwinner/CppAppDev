#ifndef LITTLEC_INTERPRETER_LCLIB_H
#define LITTLEC_INTERPRETER_LCLIB_H

#if defined(_MSC_VER)
/* if your compiler does not support this header file, remove it */
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/**
 * Points to current location in program
 */
extern char *prog;

/**
 * Holds string representation of token
 */
extern char token[80];

/**
 * Contains type of token
 */
extern char tokenType;

/**
 * Holds the internal representation of token
 */
extern char tok;

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
 * These are constants used to call sntxErr()
 * when a syntax error occurs. Add more if you like.
 * NOTE: SYNTAX is a generic error message used when
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
   NOT_STRING,
   TOO_MANY_LVARS,
   DIV_BY_ZERO
};

int getToken(void);

void sntxErr(int error);

void evalExp(int *result);

void putback(void);

/**
 * Get a character from console. (Use getchar() if
 * your compiler does not support _getche().)
 * @return Character from console
 */
int callGetche(void);

/**
 * Put a charatcer to the display
 * @return Put character
 */
int callPutch(void);

/**
 * Call puts
 * @return Put character
 */
int callPuts(void);

/**
 * A built-in console output function
 * @return
 */
int print(void);

/**
 * Read an integer from the keyboard
 * @return Read integer
 */
int getNum(void);

#endif //LITTLEC_INTERPRETER_LCLIB_H
