#ifndef LITTLEC_INTERPRETER_PARSER_H
#define LITTLEC_INTERPRETER_PARSER_H

#define _CRT_SECURE_NO_WARNINGS

#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_FUNC           100
#define NUM_GLOBAL_VARS    100
#define NUM_LOCAL_VARS     200
#define ID_LEN             32
#define FUNC_CALLS         31
#define PROG_SIZE          10000
#define FOR_NEST           31

/**
 * Token types
 */
enum tokTypes
{
   DELIMETER,
   IDENTIFIER,
   NUMBER,
   KEYWORD,
   TEMP,
   STRING,
   BLOCK
};

/**
 * Tokens
 */
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

/**
 * Operations with 2 operands
 */
enum doubleOps
{
   LT = 1,
   LE,
   GT,
   GE,
   EQ,
   NE
};

/**
 * These are the constants used to call sntxErr() when
 * a syntax error occurs. Add more if you like.
 * NOTE: Syntax is a generic error message used when
 * nothing else seems appropriate.
 */
enum errorMsg
{
   SYNTAX,
   UNBAL_PARENS,
   NO_EXP,
   EQUALS_EXPECTED,
   NOT_VAR,
   PARAM_ERR,
   SEMI_EXPECTED,
   UNBAL_BRACES,
   FUNC_UNDEF,
   TYPE_EXPECTED,
   NEST_FUNC,
   RET_NOCALL,
   PAREN_EXPECTED,
   WHILE_EXPECTED,
   QUOTE_EXPECTED,
   NOT_TEMP,
   TOO_MANY_LVARS,
   DIV_BY_ZERO
};

/**
 * Current location in source code
 */
extern char* prog;

/**
 * Points to start of program buffer
 */
extern char* p_buf;

/**
 * Hold environment for longjmp()
 */
extern jmp_buf e_buf;

/**
 * An array of these structures will hold the
 * info associated with global variables.
 */
extern struct var_type
{
   char var_name[ID_LEN];
   int v_type;
   int value;
} global_vars[NUM_GLOBAL_VARS];

/**
 * Function call stack
 */
extern struct func_type
{
   char func_name[ID_LEN];
   int ret_type;
   char* loc; /* location in function entry point in file */
} func_stack[NUM_FUNC];

/**
 * \brief Keyword table
 */
extern struct commands
{
   char command[20];
   char tok;
} table[];

/************************************************************************/
/* "standard library" functions are declared here so                *
 * they can be put into the internal function table that follows     */
/************************************************************************/

int call_getche(void), call_putch();
int call_puts(void), print(void), getnum(void);

/**
 * \brief Internal function types
 */
struct intern_func_type
{
   /**
    * \brief Function name
    */
   char* f_name;

   /**
    * \brief Function pointer
    */
   int (*p)(void);
} intern_func[] =
{
   {"getche", call_getche},
   {"putch", call_putch},
   {"puts", call_puts},
   {"print", print},
   {"getnum", getnum},
   {"", 0} /* null terminate the list */
};

/**
 * \brief string representation of token
 */
extern char token[80];

/**
 * \brief contains type of token
 */
extern char token_type;

/**
 * \brief internal representation of token
 */
extern char tok;

/**
 * \brief Function return value
 */
extern int ret_value;

void eval_exp0(int* value);

void evalExp(int* value);

void eval_exp1(int* value);

void eval_exp2(int* value);

void eval_exp3(int* value);

void eval_exp4(int* value);

void eval_exp5(int* value);

void atom(int* value);

#if defined(_MSC_VER) && _MSC_VER >= 1200
_declspec(noreturn) void sntx_err(int error);
#elif __GNUC__
void sntx_err(int error) __attribute((noreturn));
#else
void sntx_err(int error);
#endif

void putback(void);

void assign_var(char *var_name, int value);

int isdelim(char c);

int iswhite(char c);

int find_var(char *s);

int internal_func(char *s);

int is_var(char *s);

char *find_func(char *name);

char look_up(char *s);

char get_token(void);

void call(void);

static void str_replace(char *line, const char* search, const char* replace);

#endif //LITTLEC_INTERPRETER_PARSER_H
