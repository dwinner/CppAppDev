#ifndef LITTLEC_H
#define LITTLEC_H

#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "common_defines.h"

#define _CRT_SECURE_NO_WARNINGS

/**
 * \brief Current location in source code
 */
char *prog;

/**
 * \brief Points to start of program buffer
 */
char *p_buf;

/**
 * \brief Holds the environment for longjmp()
 */
jmp_buf e_buf;

/**
 * \brief   An array of these structures will hold the info
 *          associated with global variables
 */
struct var_type {
   char var_name[ID_LEN];
   int v_type;
   int value;
}  global_vars[NUM_GLOBAL_VARS];

#endif // LITTLEC_H
