#ifndef LITTLEC_LITTLEC_APP_H
#define LITTLEC_LITTLEC_APP_H

#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "littlec_parser.h"

#define NUM_FUNC        100
#define NUM_GLOBAL_VARS 100
#define NUM_LOCAL_VARS  200
#define NUM_BLOCK       100
#define ID_LEN          32
#define FUNC_CALLS      31
#define NUM_PARAMS      31
#define PROG_SIZE       10000
#define LOOP_NEST       31

// Secure function compatibility
#if !defined(_MSC_VER) || _MSC_VER < 1400
#define strcpy_s(dest, count, source) strncpy( (dest), (source), (count) )
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

/**
 * @brief Find the location of all functions in the program and store global variables
 */
void prescan(void);

/**
 * @brief Declare a global variable
 */
void decl_global(void);

/**
 * @brief Declare a local variable
 */
void decl_local(void);

/**
 * Push a local variable
 * @param i Local variable
 */
void local_push(struct var_type i);

/**
 * @brief Execute an if statement
 */
void exec_if(void);

/**
 * @brief Find the end of a block
 */
void find_eob(void);

/**
 * @brief Execute a for loop
 */
void exec_for(void);

/**
 * @brief Get function parameters
 */
void get_params(void);

/**
 * Push the arguments to a function onto the local variable stack
 */
void get_args(void);

/**
 * Execute a while loop
 */
void exec_while(void);

/**
 * Push index of local variable stack
 * @param i Index
 */
void func_push(int i);

/**
 * Execute a do loop
 */
void exec_do(void);

/**
 * Load a program
 * @param p Program
 * @param fname Function name
 * @return Status
 */
int load_program(char *p, char *fname);

/**
 * Find the value of a variable
 * @param s Variable name
 * @return Variable value
 */
int find_var(char *s);

/**
 * Assign a value to a variable
 * @param var_name Variable name
 * @param value Variable value
 */
void assign_var(char *var_name, int value);

/**
 * @brief Interpret a single statement or block of code. When
 * interp_block() returns from its initial call, the final
 * brace (or a return) in main() has been encountered.
 */
void interp_block(void);

/**
 * @brief Return from a function
 */
void func_ret(void);

/**
 * @brief Pop index into local variable stack
 * @return Index
 */
int func_pop(void);

/**
 * Determine if an identifier is a variable
 * @param s Variable name
 * @return 1 if variable is found; 0 otherwise
 */
int is_var(char *s);

/**
 * Return the entry point of the specified function. Return NULL if not found.
 * @param name Function name
 * @return Function name's entry point
 */
char *find_func(char *name);

/**
 * Call a function
 */
void call(void);

#endif //LITTLEC_LITTLEC_APP_H
