#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "eval_parser.h"

void start_evaluation(double *answer)
{
   get_token();
   
   if (!*token)
   {
      set_error(2);  /* TODO: Introduce enums for error codes */
      return;
   }

   eval_exp1(answer);

   if (*token)
   {
      /* last token must be null */
      set_error(0);  /* TODO: Introduce enums for error codes */
   }
}

void eval_exp1(double *answer)
{

}

void eval_exp2(double *answer)
{

}

void eval_exp3(double *answer)
{

}

void eval_exp4(double *answer)
{

}

void eval_exp5(double *answer)
{

}

void eval_exp6(double *answer)
{

}

void atom(double *answer)
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

double find_var(char *s)
{
   return 0.0;
}

int is_delimeter(char symbol)
{
   return 0;
}
