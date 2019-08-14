#ifndef PARSER_H

#define PARSER_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DELIMETER		1
#define VARIABLE		2
#define NUMBER			3

/**
 *	Содержит анализируемое выражение
 */
extern char *prog;
char token[80];
char token_type;

void start_evaluation(double *answer);

void add_or_subtract(double *answer);

void multiply_or_divide(double *answer);

void power(double *answer);

void unary_plus_minus(double *answer);

void eval_brackets(double *answer);

void atom(double *answer);

void get_token(void);

void putback(void);

void seterror(int error);

int is_delim(char c);

#endif // PARSER_H
