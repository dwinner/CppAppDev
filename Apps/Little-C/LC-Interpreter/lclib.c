#include "lclib.h"
#include "common_defines.h"
#include "parser.h"

/**
* Points to current location in program
*/
//extern char *prog;

/**
* Holds string representation of token
*/
//extern char token[80];

/**
* Contains type of token
*/
extern char tokenType;

/**
* Holds the internal representation of token
*/
//extern char tok;

int print(void)
{
   int i;

   get_token();
   if (*token != '(')
   {
      sntx_err(PAREN_EXPECTED);
   }

   get_token();
   if (tokenType == STRING) /* output a string */
   {
      printf("%s ", token);
   }
   else /* output a number */
   {
      putback();
      eval_exp(&i);
      printf("%d ", i);
   }

   get_token();
   if (*token != ')')
   {
      sntx_err(PAREN_EXPECTED);
   }

   get_token();
   if (*token != ';')
   {
      sntx_err(SEMI_EXPECTED);
   }

   putback();

   return 0;
}
