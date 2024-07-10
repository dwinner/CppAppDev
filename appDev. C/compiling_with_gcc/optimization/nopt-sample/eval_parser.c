//
// Created by den on 4/3/2021.
//

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

   process_assignment(answer);

   if (*token)
   {
      /* last token must be null */
      set_error(0); /* TODO: Introduce enums for error codes */
   }
}

void process_assignment(double* answer)
{
   int slot;
   TokenTypes ttokType = none;
   char temp_token[PROGRAM_BUFFER];

   if (token_type == variable)
   {
      /* save old token */
      strcpy_s(temp_token, PROGRAM_BUFFER, token);
      ttokType = token_type;

      /* compute the index of the variable */
      slot = toupper(*token) - 'A';

      get_token();

      if (*token != '=')
      {
         put_back(); /* return current token */

         /* restore old token - not assignment */
         strcpy_s(token, PROGRAM_BUFFER, temp_token);
         token_type = ttokType;
      }
      else
      {
         get_token(); /* get the next part of expression */
         process_add_or_subtract(answer);
         vars[slot] = *answer;
         return;
      }
   }

   process_add_or_subtract(answer);
}

void process_add_or_subtract(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */
   double temp;

   process_mult_or_divide(answer);

   while ((operator = *token) == '+' || operator == '-')
   {
      get_token();
      process_mult_or_divide(&temp);

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

void process_mult_or_divide(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */
   double temp;

   process_exponent(answer);

   while ((operator = *token) == '*' || operator == '/' || operator == '%')
   {
      get_token();
      process_exponent(&temp);

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

void process_exponent(double* answer)
{
   double temp, ex;
   register int t;

   evaluate_plus_or_minus(answer);
   if (*token == '^') /* TODO: Introduce enum for token types */
   {
      get_token();
      process_exponent(&temp);
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

void evaluate_plus_or_minus(double* answer)
{
   register char operator; /* TODO: Introduce enum for operator types */

   operator = 0;
   if (token_type == delimeter && *token == '+' || *token == '-')
   {
      operator = *token;
      get_token();
   }

   process_parenthesized_expr(answer);

   if (operator == '-')
   {
      *answer = -*answer;
   }
}

void process_parenthesized_expr(double* answer)
{
   if (*token == '(')
   {
      get_token();
      process_add_or_subtract(answer);
      if (*token != ')') /* TODO: Introduce enum for token types */
      {
         set_error(1); /* TODO: Introduce enum for error types */
      }

      get_token();
   }
   else
   {
      atom(answer);
   }
}

void atom(double* answer)
{
   switch (token_type)
   {
      case variable:
         *answer = find_var(token);
         get_token();
         break;

      case number:
         *answer = atof(token);
         get_token();
         break;

      default:
         set_error(0); /* TODO: Introduce enum for error types */
   }
}

void get_token(void)
{
   register char* temp;

   token_type = none;
   temp = token;
   *temp = '\0';

   if (!*program)
   {
      return; /* At the end of expression */
   }

   /* Skip over white spaces */
   while (isspace(*program))
   {
      ++program;
   }

   /* TODO: Introduce delimeter types */
   if (strchr("+-*/%^=()", *program))
   {
      token_type = delimeter;
      *temp++ = *program++; /* advance to the next char */
   }
   else if (isalpha(*program))
   {
      while (!is_delimeter(*program)) /* TOREFACTOR: Move it to function */
      {
         *temp++ = *program++;
      }

      token_type = variable;
   }
   else if (isdigit(*program))
   {
      while (!is_delimeter(*program)) /* TOREFACTOR: Move it to function */
      {
         *temp++ = *program++;
      }

      token_type = number;
   }

   *temp = '\0';
}

void put_back(void)
{
   char* charToRet;

   charToRet = token;
   for (; *charToRet; charToRet++)
   {
      program--;
   }
}

void set_error(const int errorIndex)
{
   /* Due to recursive nature, you can get a lot of errors.
      If you want to stop on the first error, use longjmp()/setjmp() */
   static char* errorTypes[] =
       {
           "Syntax Error",
           "Unbalanced Parentheses",
           "No Expression Present",
           "Division by Zero"
       };

   printf("%s\n", errorTypes[errorIndex]);
}

double find_var(const char* symbol)
{
   if (!isalpha(*symbol))
   {
      set_error(1);
      return 0.0;
   }

   return vars[toupper(*token) - 'A'];
}

/* TODO: Use _Bool for all such return values and checking */
int is_delimeter(char symbol)
{
   /* TODO: Introduce delimeter types */
   return strchr(" +-/*%^=()", symbol) || symbol == 9 || symbol == '\r' || symbol == 0
          ? 1
          : 0;
}

