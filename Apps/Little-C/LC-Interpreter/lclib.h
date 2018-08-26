#ifndef LITTLEC_INTERPRETER_LCLIB_H
#define LITTLEC_INTERPRETER_LCLIB_H

#if defined(_MSC_VER)
/* if your compiler does not support this header file, remove it */
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>

//int get_token(void);

//void sntx_err(int error);

//void eval_exp(int *result);

//void putback(void);

/**
 * A built-in console output function
 * @return
 */
int print(void);

#endif //LITTLEC_INTERPRETER_LCLIB_H
