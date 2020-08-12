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
void process_assignment(double* answer);

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

/**
 * \brief Process a parenthesized expression
 * \param answer Recursively return expression value
 */
void eval_exp6(double* answer);

/**
 * \brief Get the value of a number or a variable
 * \param answer Recursively return expression value
 */
void atom(double* answer);

/**
 * \brief Return the next token
 */
void get_token(void);

/**
 * \brief Return a token to the input stream
 */
void put_back(void);

/**
 * \brief Display a syntax error
 * \param errorIndex Error type
 */
void set_error(int errorIndex);

/**
 * \brief Get variable value
 * \param symbol Variable symbol
 * \return Variable value
 */
double find_var(char* symbol);

/**
 * \brief Finds out if the symbol is delimeter or not
 * \param symbol The symbol
 * \return True if the symbol is a delimeter
 */
int is_delimeter(char symbol);

#endif // EVAL_PARSER_H
