/**
 * Internal library functions
 */

#ifndef LITTLEC_LITTLEC_LIB_H
#define LITTLEC_LITTLEC_LIB_H

#if defined(_MSC_VER)
/* if your compiler does not support this  header file, remove it */
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/**
 * Token types
 */
enum tok_types
{
   DELIMITER,
   IDENTIFIER,
   NUMBER,
   KEYWORD,
   TEMP,
   STRING,
   BLOCK
};

/**
 * These are the constants used to call sntx_err() when a syntax error occurs.
 * @remarks Add more if you like.
 * @note SYNTAX is a generic error message used when nothing else seems appropriate.
 */
enum error_msg
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

/**
 * @brief Get a character from console.
 * @note (Use getchar() if your compiler does not support _getche().)
 * @return A character
 */
int call_getche(void);

/**
 * @brief Put a character to the display.
 * @return A character
 */
int call_putch(void);

/**
 * @brief Call puts().
 * @return 0 after processing
 */
int call_puts(void);

/**
 * @brief A built-in console output function.
 * @return 0 after processing
 */
int print(void);

/**
 * Read an integer from the keyboard.
 * @return
 */
int getnum(void);

#endif //LITTLEC_LITTLEC_LIB_H
