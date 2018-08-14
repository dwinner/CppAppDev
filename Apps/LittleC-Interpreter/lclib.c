#include "lclib.h"

int callGetche(void)
{
   char ch;
#if defined(_QC)
   ch = (char) getche();
#elif defined(_MSC_VER)
   ch = (char) _getche();
#else
   ch = (char) getchar();
#endif

   while (*prog != ')')
      prog++;

   prog++;  /* advance to end of line */

   return ch;
}

int callPutch(void)
{
   int value;

   evalExp(&value);
   printf("%c", value);

   return value;
}

int callPuts(void)
{
   getToken();
   if (*token != '(')
      sntxErr(PAREN_EXPECTED);

   getToken();
   if (tokenType != STRING)
      sntxErr(QUOTE_EXPECTED);

   puts(token);
   getToken();
   if (*token != ')')
      sntxErr(PAREN_EXPECTED);

   getToken();
   if (*token != ';')
      sntxErr(SEMI_EXPECTED);

   putback();

   return 0;
}

int print(void)
{
   int i;

   getToken();
   if (*token != '(')
      sntxErr(PAREN_EXPECTED);

   getToken();
   if (tokenType == STRING)  /* output a string */
   {
      printf("%s ", token);
   }
   else  /* output a number */
   {
      putback();
      evalExp(&i);
      printf("%d ", i);
   }

   getToken();
   if (*token != ')')
      sntxErr(PAREN_EXPECTED);

   getToken();
   if (*token != ';')
      sntxErr(SEMI_EXPECTED);

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

      prog++;  /* advance to end of line */
      return atoi(s);
   }

   return 0;
}
