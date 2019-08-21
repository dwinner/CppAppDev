#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "eval_parser.h"

void start_evaluation(double* answer)
{
   get_token();

   if (!*token)
   {
      set_error(2); /* TODO: Introduce enums for error codes */
      return;
   }

   eval_exp1(answer);

   if (*token)
   {
      /* last token must be null */
      set_error(0); /* TODO: Introduce enums for error codes */
   }
}

void eval_exp1(double* answer)
{
   int slot;
   char ttok_type;
   char temp_token[PROGRAM_BUFFER];

   if (token_type == VARIABLE)
   {
      /* save old token */
      strcpy_s(temp_token, PROGRAM_BUFFER, token);
      ttok_type = token_type;

      /* compute the index of the variable */
      slot = toupper(*token) - 'A';

      get_token();

      if (*token != '=')
      {
         put_back(); /* return current token */

         /* restore old token - not assignment */
         strcpy_s(token, PROGRAM_BUFFER, temp_token);
         token_type = ttok_type;
      }
      else
      {
         get_token(); /* get the next part of expression */
         eval_exp2(answer);
         vars[slot] = *answer;
         return;
      }
   }

   eval_exp2(answer);
}

void eval_exp2(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */
   double temp;

   eval_exp3(answer);

   while ((operator = *token) == '+' || operator == '-')
   {
      get_token();
      eval_exp3(&temp);

      switch (operator) /* TOREFACTOR: Move it to function */
      {
      case '-':
         *answer -= temp;
         break;

      case '+':
         *answer += temp;
         break;

      default:
         break;
      }
   }
}

void eval_exp3(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */
   double temp;

   eval_exp4(answer);

   while ((operator = *token) == '*' || operator == '/' || operator == '%')
   {
      get_token();
      eval_exp4(&temp);

      switch (operator) /* TODO: Move it to function */
      {
      case '*':
         *answer *= temp;
         break;

      case '/':
         if (temp == 0.0)
         {
            /* TODO: Introduce enum for error types */
            set_error(3); /* division by zero */
            *answer = 0.0;
         }
         else
         {
            *answer /= temp;
         }
         break;

      case '%':
         *answer = (int)*answer % (int)temp;
         break;

      default:
         break;
      }
   }
}

void eval_exp4(double* answer)
{
   double temp, ex;
   register int t;

   eval_exp5(answer);
   if (*token == '^')
   {
      get_token();
      eval_exp4(&temp);
      ex = *answer;
      if (temp == 0.0)
      {
         *answer = 1.0;
         return;
      }

      for (t = temp - 1; t > 0; --t)
      {
         *answer *= (double)ex;
      }
   }
}

void eval_exp5(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */

   operator = 0;
   if ((token_type == DELIMETER) && *token == '+' || *token == '-')
   {
      operator = *token;
      get_token();
   }

   eval_exp6(answer);

   if (operator == '-')
   {
      *answer = -*answer;
   }
}

void eval_exp6(double* answer)
{
}

void atom(double* answer)
{
}

void get_token(void)
{
}

void put_back(void)
{
}

void set_error(int error)
{
}

double find_var(char* s)
{
   return 0.0;
}

int is_delimeter(char symbol)
{
   return 0;
}
