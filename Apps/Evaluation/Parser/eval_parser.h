#ifndef EVAL_PARSER_H
#define EVAL_PARSER_H

/**
 * \brief Type of tokens
 */
enum token_types
{
   none = 0,
   delimeter = 1,
   variable,
   number
};

typedef enum token_types TokenTypes;

#define PROGRAM_BUFFER  80
#define VARIABLE_NUMBER 26

/**
 * Points to the expression to be analyzed
 */
extern char* program;

/**
 * 26 user variables, A-Z
 */
extern double vars[];

char token[PROGRAM_BUFFER];

TokenTypes token_type;

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
void process_add_or_subtract(double* answer);

/**
 * \brief Multiply or divide two factors
 * \param answer Recursively return expression value
 */
void process_mult_or_divide(double* answer);

/**
 * \brief Process an exponent
 * \param answer Recursively return expression value
 */
void process_exponent(double* answer);

/**
 * \brief Evaluate an unary + or -
 * \param answer Recursively return expression value
 */
void evaluate_plus_or_minus(double* answer);

/**
 * \brief Process a parenthesized expression
 * \param answer Recursively return expression value
 */
void process_parenthesized_expr(double* answer);

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
double find_var(const char* symbol);

/**
 * \brief Finds out if the symbol is delimeter or not
 * \param symbol The symbol
 * \return True if the symbol is a delimeter
 */
int is_delimeter(char symbol);

#endif // EVAL_PARSER_H
