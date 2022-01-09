/**
 * Recursive descent parser for integer expressions
 * which may include variables and function calls.
 */

#ifndef LITTLEC_LITTLEC_PARSER_H
#define LITTLEC_LITTLEC_PARSER_H

#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "littlec_lib.h"

#define NUM_FUNC        100
#define NUM_GLOBAL_VARS 100
#define NUM_LOCAL_VARS  200
#define ID_LEN          32
#define FUNC_CALLS      31
#define PROG_SIZE       10000
#define FOR_NEST        31

// Secure function compatibility
#if !defined(_MSC_VER) || _MSC_VER < 1400
#define strcpy_s(dest, count, source) strncpy( (dest), (source), (count) )
#endif

enum tokens
{
   ARG,
   CHAR,
   INT,
   IF,
   ELSE,
   FOR,
   DO,
   WHILE,
   SWITCH,
   RETURN,
   CONTINUE,
   BREAK,
   EOL,
   FINISHED,
   END
};

enum double_ops
{
   LT = 1,
   LE,
   GT,
   GE,
   EQ,
   NE
};

/**
 * @brief An array of these structures will hold the info associated with global variables.
 */
struct var_type
{
   char var_name[ID_LEN];
   int v_type;
   int value;
} global_vars[NUM_GLOBAL_VARS];

/**
 * @brief This is the function call stack.
 */
struct func_type
{
   /**
    * Function name
    */
   char func_name[ID_LEN];

   /**
    * Return type
    */
   int ret_type;

   /**
    * Location of function entry point in file
    */
   char *loc;
} func_stack[NUM_FUNC];

/**
 * @brief Keyword table
 */
struct commands
{
   char command[20];
   char tok;
} table[];

struct intern_func_type
{
   char *f_name; /* function name */
   int (*p)(void);   /* pointer to the function */
} intern_func[] =
    {
        {"getche", call_getche},
        {"putch",  call_putch},
        {"puts",   call_puts},
        {"print",  print},
        {"getnum", getnum},
        {"",       0} /* null terminate the list */
    };

//int get_token(void);

//void sntx_err(int error);

/**
 * @brief Entry point into parser.
 * @param result points to current result
 */
void eval_exp(int *result);

/**
 * Process an assignment expression
 * @param value
 */
void eval_exp0(int *value);

/**
 * Process relational operators.
 * @param value
 */
void eval_exp1(int *value);

/**
 * Add or subtract two terms.
 * @param value
 */
void eval_exp2(int *value);

/**
 * Multiply or divide two factors.
 * @param value
 */
void eval_exp3(int *value);

/**
 * Is a unary + or -.
 * @param value
 */
void eval_exp4(int *value);

/**
 * Process parenthesized expression.
 * @param value
 */
void eval_exp5(int *value);

/**
 * Find value of number, variable, or function.
 * @param value
 */
void atom(int *value);

void putback(void);

#if defined(_MSC_VER) && _MSC_VER >= 1200
__declspec(noreturn) void sntx_err(int error);
#elif __GNUC__

/**
 * Display an error message.
 * @param error
 */
void sntx_err(int error) __attribute((noreturn));

#else
void sntx_err(int error);
#endif

void assign_var(char *var_name, int value);

int isdelim(char c);

int iswhite(char c);

int find_var(char *s);

int internal_func(char *s);

int is_var(char *s);

char *find_func(char *name);

char look_up(char *s);

/**
 * Get a token.
 * @return
 */
char get_token(void);

void call(void);

static void str_replace(char *line, const char *search, const char *replace);

#endif //LITTLEC_LITTLEC_PARSER_H
