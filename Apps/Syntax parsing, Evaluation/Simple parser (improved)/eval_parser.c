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
   if (*token == '^') /* TODO: Introduce enum for token types */
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
   if (token_type == DELIMETER && *token == '+' || *token == '-')
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
   if (*token == '(')
   {
      get_token();
      eval_exp2(answer);
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
   switch (token_type) /* TODO: Introduce enum for token types */
   {
   case VARIABLE:
      *answer = find_var(token);
      get_token();
      return;

   case NUMBER:
      *answer = atof(token);
      get_token();
      return;

   default:
      set_error(0); /* TODO: Introduce enum for error types */
   }
}

void get_token(void)
{
   register char* temp;

   token_type = 0;
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
      token_type = DELIMETER;
      *temp++ = *program++; /* advance to the next char */
   }
   else if (isalpha(*program))
   {
      while (!is_delimeter(*program)) /* TOREFACTOR: Move it to function */
      {
         *temp++ = *program++;
      }

      token_type = VARIABLE;
   }
   else if (isdigit(*program))
   {
      while (!is_delimeter(*program)) /* TOREFACTOR: Move it to function */
      {
         *temp++ = *program++;
      }

      token_type = NUMBER;
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

void set_error(int errorIndex)
{
   /* NOTE: Due to recursive nature, you can get a lot of errors.
    * If you want to stop on the first error, use longjmp()/setjmp()
    */
   static char* error_types[] =
   {
      "Syntax Error",
      "Unbalanced Parentheses",
      "No Expression Present",
      "Division by Zero"
   };

   printf("%s\n", error_types[errorIndex]);
}

double find_var(char* symbol)
{
   if (!isalpha(*symbol))
   {
      set_error(1); /* TODO: Introduce enum for error types */
      return 0.0;
   }

   return vars[toupper(*token) - 'A']; /* TOREFACTOR: Strange way to obtain variable value */
}

/* TODO: Use _Bool for all such return values and checking */
int is_delimeter(char symbol)
{
   /* TODO: Introduce delimeter types */
   return strchr(" +-/*%^=()", symbol) || symbol == 9 || symbol == '\r' || symbol == 0
             ? 1
             : 0;
}
