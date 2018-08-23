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

int get_token(void);

void sntx_err(int error);

void eval_exp(int *result);

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
