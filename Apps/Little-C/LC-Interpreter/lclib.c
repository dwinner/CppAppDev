#include "lclib.h"
#include "common_defines.h"

int callGetche(void)
{
   char ch;
#if defined(_QC)
   ch = (char) getche();
#elif defined(_MSC_VER)
   ch = (char)_getche();
#else
   ch = (char) getchar();
#endif

   while (*prog != ')')
      prog++;

   prog++; /* advance to end of line */

   return ch;
}

int callPutch(void)
{
   int value;

   eval_exp(&value);
   printf("%c", value);

   return value;
}

int callPuts(void)
{
   get_token();
   if (*token != '(')
      sntx_err(PAREN_EXPECTED);

   get_token();
   if (tokenType != STRING)
      sntx_err(QUOTE_EXPECTED);

   puts(token);
   get_token();
   if (*token != ')')
      sntx_err(PAREN_EXPECTED);

   get_token();
   if (*token != ';')
      sntx_err(SEMI_EXPECTED);

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

int getNum(void)
{
   char s[80];

   if (fgets(s, sizeof(s), stdin) != NULL)
   {
      while (*prog != ')')
         prog++;

      prog++; /* advance to end of line */
      return atoi(s);
   }

   return 0;
}
