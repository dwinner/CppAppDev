#ifndef EVAL_PARSER_H
#define EVAL_PARSER_H

/* TODO: Introduce enum for type of tokens  */
#define DELIMETER 1
#define VARIABLE  2
#define NUMBER    3
#define PROGRAM_BUFFER  80
#define VARIABLE_NUMBER 26

/**
 * Points to the expression to be analyzed
 */
extern char* program; /* TOREFACTOR: Encapsulate global/extern declarations */

/**
 * 26 user variables, A-Z
 */
extern double vars[]; /* TOREFACTOR: Encapsulate global/extern declarations */

char token[PROGRAM_BUFFER]; /* TOREFACTOR: Encapsulate global/extern declarations */

/* TOREFACTOR: Encapsulate global/extern declarations */
char token_type;

/**
 * \brief Parser entry point
 * \param answer Recursive buffer value
 */
void start_evaluation(double* answer);

/**
 * \brief Process an assignment
 * \param answer Recursively return expression value
 */
void eval_exp1(double* answer);

/**
 * \brief Add or subtract two terms
 * \param answer Recursively return expression value
 */
void eval_exp2(double* answer);

/**
 * \brief Multiply or divide two factors
 * \param answer Recursively return expression value
 */
void eval_exp3(double* answer);

/**
 * \brief Process an exponent
 * \param answer Recursively return expression value
 */
void eval_exp4(double* answer);

/**
 * \brief Evaluate an unary + or -
 * \param answer Recursively return expression value
 */
void eval_exp5(double* answer);

void eval_exp6(double* answer);

void atom(double* answer);

void get_token(void);

void put_back(void);

void set_error(int error);

double find_var(char* s);

int is_delimeter(char symbol);

#endif // EVAL_PARSER_H
