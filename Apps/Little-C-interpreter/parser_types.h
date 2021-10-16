#ifndef LITTLE_C_INTERPRETER_PARSER_TYPES_H
#define LITTLE_C_INTERPRETER_PARSER_TYPES_H

#define NUM_FUNC        100
#define NUM_GLOBAL_VARS 100
#define NUM_LOCAL_VARS  200
#define ID_LEN          31
#define FUNC_CALLS      31
#define PROG_SIZE       10000
#define FOR_NEST        31

/**
 * Error message types
 */
enum error_msg
{
   /**
    * Generic error message
    */
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
 * Token types
 */
enum tok_types
{
   DELIMITER,
   IDENTIFIER,
   NUMBER,
   KEYWORD,
   TEMP,
   STRING,
   BLOCK
};

/**
 * Reserved tokens
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
   EOL,
   FINISHED,
   END
};

/**
 * Operation types for at least 2 operands
 */
enum double_ops
{
   LT = 1,
   LE,
   GT,
   GE,
   EQ,
   NE
};


#endif //LITTLE_C_INTERPRETER_PARSER_TYPES_H
