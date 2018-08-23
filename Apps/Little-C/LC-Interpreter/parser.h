#ifndef LITTLEC_INTERPRETER_PARSER_H
#define LITTLEC_INTERPRETER_PARSER_H

#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <setjmp.h>
#include "common_defines.h"

/**
 * Additional double operators here (such as ->)
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

/************************************************************************/
/* "standard library" functions are declared here so                    *
 * they can be put into the internal function table that follows        */
/************************************************************************/

int call_getche(void);

int call_putch();

int call_puts(void);

int print(void);

int getnum(void);

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

void eval_exp(int* value);

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

void assign_var(char* var_name, int value);

int isdelim(char c);

int iswhite(char c);

int find_var(char* s);

int internal_func(char* s);

int is_var(char* s);

char* find_func(char* name);

char look_up(char* s);

char get_token(void);

void call(void);

static void str_replace(char* line, const char* search, const char* replace);

#endif //LITTLEC_INTERPRETER_PARSER_H
