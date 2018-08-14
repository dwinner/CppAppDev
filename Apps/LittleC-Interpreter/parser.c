/**
 * Recursive descent parser for integer expressions
 * which may include variables and function calls.
 */

#include "parser.h"

/**
 * \brief Process an assignment expression
 * \param value Value to parse
 */
void eval_exp0(int* value)
{
   char temp[ID_LEN]; /* holds name of var receiving the assignment */
   register char temp_tok;

   if (token_type == IDENTIFIER)
   {
      if (is_var(token)) /* if a var, see if assignment */
      {
         strcpy(temp, token);
         temp_tok = token_type;
         get_token();
         if (*token == '=') /* is an assignment */
         {
            get_token();
            eval_exp0(value); /* get value to assign */
            assign_var(temp, *value); /* assign the value */
            return;
         }
         /* not an assignment */
         putback(); /* restore original token */
         strcpy(token, temp);
         token_type = temp_tok;
      }
   }

   eval_exp1(value);
}

/**
 * \brief Entry point to parser
 * \param value Value to parse
 */
void evalExp(int* value)
{
   get_token();
   if (!*token)
   {
      sntx_err(NO_EXP);
      return;
   }

   if (*token == ';')
   {
      *value = 0; /* empty expression */
      return;
   }

   eval_exp0(value);
   putback(); /* return last token read to input stream */
}

/**
 * \brief Process relational operators
 * \param value Value to process
 */
void eval_exp1(int* value)
{
   int partial_value;
   register char op;
   char relops[7] = {LT, LE, GT, GE, EQ, NE, 0};

   eval_exp2(value);
   op = *token;
   if (strchr(relops, op))
   {
      get_token();
      eval_exp2(&partial_value);
      switch (op) /* perform the relational operation */
      {
      case LT:
         *value = *value < partial_value;
         break;
      case LE:
         *value = *value <= partial_value;
         break;
      case GT:
         *value = *value > partial_value;
         break;
      case GE:
         *value = *value >= partial_value;
         break;
      case EQ:
         *value = *value == partial_value;
         break;
      case NE:
         *value = *value != partial_value;
         break;
      }
   }
}

/**
 * \brief Add or subtract two terms
 * \param value Value to process
 */
void eval_exp2(int* value)
{
   register char op;
   int partial_value;

   eval_exp3(value);
   op = *token;
   while (op == '+' || op == '-')
   {
      get_token();
      eval_exp3(&partial_value);
      switch (op) /* Add or subtract */
      {
      case '-':
         *value = *value - partial_value;
         break;
      case '+':
         *value = *value + partial_value;
         break;
      }
   }
}

/**
 * \brief Multiply or divide two factors
 * \param value Value to parse
 */
void eval_exp3(int* value)
{
   register char op;
   int partial_value, t;

   eval_exp4(value);
   op = *token;
   while (op == '*' || op == '/' || op == '%')
   {
      get_token();
      eval_exp4(&partial_value);
      switch (op) /* mul, div, or modulus */
      {
      case '*':
         *value = *value * partial_value;
         break;
      case '/':
         if (partial_value == 0)
         {
            sntx_err(DIV_BY_ZERO);
         }

         *value = (*value) / partial_value;
         break;
      case '%':
         t = (*value) / partial_value;
         *value = *value - (t * partial_value);
         break;
      }
   }
}

/**
 * \brief Is unary '+' or '-' token
 * \param value Value to parse
 */
void eval_exp4(int* value)
{
   register char op;

   op = '\0';
   if (*token == '+' || *token == '-')
   {
      op = *token;
      get_token();
   }

   eval_exp5(value);
   if (op && op == '-')
   {
      *value = -(*value);
   }
}

/**
 * \brief Process parenthesized expression
 * \param value Value to parse
 */
void eval_exp5(int* value)
{
   if (*token == '(')
   {
      get_token();
      eval_exp0(value); /* get subexpression */
      if (*token != ')')
      {
         sntx_err(PAREN_EXPECTED);
      }

      get_token();
   }
   else
   {
      atom(value);
   }
}
