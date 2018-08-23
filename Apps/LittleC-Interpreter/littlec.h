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

/**
 * \brief Local variable stack
 */
struct var_type local_var_stack[NUM_LOCAL_VARS];

/**
 * \brief Function type table
 */
struct func_type
{
   /**
    * \brief Function name
    */
   char func_name[ID_LEN];
   
   /**
    * \brief Return type
    */
   int ret_type;

   /**
    * \brief Location od entry point in file
    */
   char *loc;
} func_table[NUM_FUNC];

/**
 * \brief Call stack
 */
int call_stack[NUM_FUNC];

/**
 * \brief keyword lookup table
 * \details Commands must be entered lowercase
 */
struct commands
{
   char command[20];
   char tok;
} table[] =
{
   { "if", IF }, /* in this table. */
   { "else", ELSE },
   { "for", FOR },
   { "do", DO },
   { "while", WHILE },
   { "char", CHAR },
   { "int", INT },
   { "return", RETURN },
   { "continue", CONTINUE },
   { "break", BREAK },
   { "end", END },
   { "", END } /* mark end of table */
};

/**
 * \brief string representation of token
 */
char token[80];

/**
 * \brief contains type of token
 */
char token_type;

/**
 * \brief internal representation of token
 */
char tok;

/**
 * \brief Index to top of function call stack
 */
int functos;

/**
 * \brief Index into function table
 */
int func_index;

/**
 * \brief Index into global variable table
 */
int gvar_index;

/**
 * \brief Index into local variable stack
 */
int lvartos;

/**
 * \brief Function return value
 */
int ret_value;

/**
 * \brief Function return is occuring
 */
int ret_occurring;

/**
 * \brief Loop break is occuring
 */
int break_occuring;

void print(void);

void prescan(void);

void decl_global(void);

void call(void);

void putback(void);

void decl_local(void);

void local_push(struct var_type i);

void eval_exp(int *value);

void sntx_err(int error);

void exec_if(void);

void find_eob(void);

void exec_for(void);

void get_params(void);

void get_args(void);

void exec_while(void);

void func_push(int i);

void exec_do(void);

void assign_var(char *var_name, int value);

int load_program(char *p, char *fname);

int find_var(char *s);

void interp_block(void);

void func_ret(void);

int func_pop(void);

int is_var(char *s);

char *find_func(char *name);

char get_token(void);

#endif // LITTLEC_H
