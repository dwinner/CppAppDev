/**
 * A Little C interpreter
 */

#include "littlec.h"

#define _CRT_SECURE_NO_WARNINGS

/**
 * \brief Load a program
 * \param p Current symbol to process
 * \param fname File name
 * \return 1 - if loading is Ok, 0 - otherwise
 */
int load_program(char* p, char* fname)
{
   FILE *fp;
   int i;

   if ((fp=fopen(fname,"rb"))==NULL)
   {
      return 0;
   }

   i = 0;
   do
   {
      *p = (char)getc(fp);
      p++;
      i++;
   }
   while (!feof(fp)&&i<PROG_SIZE);

   if (*(p-2)==0x1a)
   {
      *(p - 2) = '\0';  /* null terminate the program */
   }
   else
   {
      *(p - 1) = '\0';
   }

   fclose(fp);

   return 1;
}

/**
 * \brief Interpret a single statement or block of code.
 * \details When interp_block() returns from its initial call,
 * the final brace (or a return) int main() has been encountered.
 */
void interp_block(void)
{
   int value;
   char block = 0;

   do
   {
      token_type = get_token();

      /* If interpreting single statement, return on
         first semicolon */

      /* see what kind of token is up */
      if (token_type==IDENTIFIER)
      {
         /* Not a keyword, so process expression */
         putback();  /* restore token to input stream for further processing by eval_exp() */
         eval_exp(&value); /* process the expression */
         if (*token != ';')
         {
            sntx_err(SEMI_EXPECTED);
         }
      }
      else if (token_type == BLOCK)   /* if block delimeter */
      {
         if (*token == '{')  /* is a block */
         {
            block = 1;  /* interpreting block, not statement */
         }
         else
         {
            return;  /* is a }, so return */
         }
      }
      else  /* is keyword */
      {
         switch (tok)
         {
         case CHAR:
         case INT:   /* declare local variables */
            putback();
            decl_local();
            break;
         case RETURN:   /* return from function call */
            func_ret();
            ret_occurring = 1;
            return;
         case CONTINUE: /* continue loop expression */
            return;
         case BREAK: /* break loop expression */
            break_occuring = 1;
            return;
         case IF: /* process an if statement */
            exec_if();
            if (ret_occurring>0 || break_occuring>0)
            {
               return;
            }
            break;
         case ELSE:  /* process an else statement */
            find_eob(); /* find end of else block and continue execution */
            break;
         case WHILE: /* process a while loop */
            exec_while();
            if (ret_occurring>0)
            {
               return;
            }
            break;
         case DO: /* process a do-while loop */
            exec_do();
            if (ret_occurring>0)
            {
               return;
            }
            break;
         case FOR:   /* process a for loop */
            exec_for();
            if (ret_occurring>0)
            {
               return;
            }
            break;
         case END:
            exit(0);
         }
      }
   }
   while (tok!=FINISHED && block);
}
