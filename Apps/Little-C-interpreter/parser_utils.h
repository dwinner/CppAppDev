#ifndef LITTLE_C_INTERPRETER_PARSER_UTILS_H
#define LITTLE_C_INTERPRETER_PARSER_UTILS_H

#include <setjmp.h>

char *p_buf;

char *prog;

jmp_buf e_buf;

/**
 * Display an error message
 * @param error Error type
 */
void sntx_err(int error);

#endif //LITTLE_C_INTERPRETER_PARSER_UTILS_H
