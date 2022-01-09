#include "littlec_lib.h"
#include "littlec_parser.h"

/**
 * points to current location in program
 */
extern char *prog;

/**
 * holds string representation of token
 */
extern char token[80];

/**
 * contains type of token
 */
extern char token_type;

/**
 * holds the internal representation of token
 */
extern char tok;

int call_getche(void)
{
   char ch;

#if defined(_QC)
   ch = (char)getche();
#elif defined(_MSC_VER)
   ch = (char)_getche();
#else
   ch = (char) getchar();
#endif

   while (*prog != ')')
   {
      prog++;
   }

   prog++;   /* advance to end of line */

   return ch;
}

int call_putch(void)
{
   int value;

   eval_exp(&value);
   printf("%c", value);

   return value;
}

int call_puts(void)
{
   get_token();
   if (*token != '(')
   {
      sntx_err(PAREN_EXPECTED);
   }

   get_token();
   if (token_type != STRING)
   {
      sntx_err(QUOTE_EXPECTED);
   }

   puts(token);
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

int print(void)
{
   int i;

   get_token();
   if (*token != '(')
   {
      sntx_err(PAREN_EXPECTED);
   }

   get_token();
   if (token_type == STRING)
   {
      /* output a string */
      printf("%s ", token);
   }
   else
   {
      /* output a number */
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

int getnum(void)
{
   char s[80];

   if (fgets(s, sizeof(s), stdin) != NULL)
   {
      while (*prog != ')')
      {
         prog++;
      }

      prog++;  /* advance to end of line */
      return atoi(s);
   }
   else
   {
      return 0;
   }
}
