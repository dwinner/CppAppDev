#ifndef EVAL_PARSER_H
#define EVAL_PARSER_H

#define DELIMETER 1
#define VARIABLE  2
#define NUMBER    3
#define PROGRAM_BUFFER  80
#define VARIABLE_NUMBER 26

/**
 * Points to the expression to be analyzed
 */
extern char *program;

char token[PROGRAM_BUFFER];

char token_type;

#endif // EVAL_PARSER_H
