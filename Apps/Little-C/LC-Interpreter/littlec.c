/**
 * A Little C interpreter
 */

#include "littlec.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

/**
 * \brief Assign a value to a variable
 * \param var_name Variable name
 * \param value Value
 */
void assign_var(char *var_name, int value)
{
   register int i;

   /* first, see if it's a local variable */
   for (i = lvartos - 1; i >= call_stack[functos - 1]; i--)
   {
      if (!strcmp(local_var_stack[i].var_name, var_name))
      {
         local_var_stack[i].value = value;
         return;
      }
   }

   if (i < call_stack[functos - 1])
   {
      /* if not local, try global var table */
      for (i = 0; i < NUM_GLOBAL_VARS; i++)
      {
         if (!strcmp(global_vars[i].var_name, var_name))
         {
            global_vars[i].value = value;
            return;
         }
      }
   }

   sntx_err(NOT_VAR); /* variable not found */
}

/**
 * \brief Load a program
 * \param p Current symbol to process
 * \param fname File name
 * \return 1 - if loading is Ok, 0 - otherwise
 */
int load_program(char *p, char *fname)
{
   FILE *fp;
   int i;

   if ((fp = fopen(fname, "rb")) == NULL)
   {
      return 0;
   }

   i = 0;
   do
   {
      *p = (char) getc(fp);
      p++;
      i++;
   } while (!feof(fp) && i < PROG_SIZE);

   if (*(p - 2) == 0x1a)
   {
      *(p - 2) = '\0'; /* null terminate the program */
   }
   else
   {
      *(p - 1) = '\0';
   }

   fclose(fp);

   return 1;
}

/**
 * \brief Find the value of a variable
 * \param s Variable name
 * \return Value
 */
int find_var(char *s)
{
   register int i;

   /* fisrt, see if it's a local variable */
   for (i = lvartos - 1; i >= call_stack[functos - 1]; i--)
   {
      if (!strcmp(local_var_stack[i].var_name, token))
      {
         return local_var_stack[i].value;
      }
   }

   /* otherwise, try global vars */
   for (i = 0; i < NUM_GLOBAL_VARS; i++)
   {
      if (!strcmp(global_vars[i].var_name, s))
      {
         return global_vars[i].value;
      }
   }

   sntx_err(NOT_VAR); /* variable not found */
   return -1;
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
      if (token_type == IDENTIFIER)
      {
         /* Not a keyword, so process expression */
         putback(); /* restore token to input stream for further processing by eval_exp() */
         eval_exp(&value); /* process the expression */
         if (*token != ';')
         {
            sntx_err(SEMI_EXPECTED);
         }
      }
      else if (token_type == BLOCK) /* if block delimeter */
      {
         if (*token == '{') /* is a block */
         {
            block = 1; /* interpreting block, not statement */
         }
         else
         {
            return; /* is a }, so return */
         }
      }
      else /* is keyword */
      {
         switch (tok)
         {
            case CHAR:
            case INT: /* declare local variables */
               putback();
               decl_local();
               break;
            case RETURN: /* return from function call */
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
               if (ret_occurring > 0 || break_occuring > 0)
               {
                  return;
               }
               break;
            case ELSE: /* process an else statement */
               find_eob(); /* find end of else block and continue execution */
               break;
            case WHILE: /* process a while loop */
               exec_while();
               if (ret_occurring > 0)
               {
                  return;
               }
               break;
            case DO: /* process a do-while loop */
               exec_do();
               if (ret_occurring > 0)
               {
                  return;
               }
               break;
            case FOR: /* process a for loop */
               exec_for();
               if (ret_occurring > 0)
               {
                  return;
               }
               break;
            case END:
               exit(0);
            default:
               break;
         }
      }
   } while (tok != FINISHED && block);
}

/**
 * \brief Return from a function
 */
void func_ret()
{
   int value;

   value = 0;
   /* get return value, if any */
   eval_exp(&value);
   ret_value = value;
}

/**
 * \brief Pop index into local variable stack
 * \return Index
 */
int func_pop()
{
   int index = 0;
   functos--;
   if (functos < 0)
   {
      sntx_err(RET_NOCALL);
   }
   else if (functos >= NUM_FUNC)
   {
      sntx_err(NEST_FUNC);
   }
   else
   {
      index = call_stack[functos];
   }

   return index;
}

/**
 * \brief Determine if an identifier is a variable.
 * \param s Identifier
 * \return 1 if variable is found; 0 otherwise
 */
int is_var(char *s)
{
   register int i;

   /* first, see if it's a local variable */
   for (i = lvartos - 1; i >= call_stack[functos - 1]; i--)
   {
      if (!strcmp(local_var_stack[i].var_name, token))
      {
         return 1;
      }
   }

   /* otherwise, try global vars */
   for (i = 0; i < NUM_GLOBAL_VARS; i++)
   {
      if (!strcmp(global_vars[i].var_name, s))
      {
         return 1;
      }
   }

   return 0;
}

/**
* \brief Declare a global variable
*/
void decl_global()
{
   int vartype;

   get_token(); /* get type */
   vartype = tok; /* save var type */
   do /* process comma-separated list */
   {
      global_vars[gvar_index].v_type = vartype;
      global_vars[gvar_index].value = 0; /* init to 0 */
      get_token(); /* get name */
      strcpy(global_vars[gvar_index].var_name, token);
      get_token();
      gvar_index++;
   } while (*token == ',');

   if (*token != ';')
   {
      sntx_err(SEMI_EXPECTED);
   }
}

/**
 * \brief Call a function
 */
void call()
{
   char *loc, *temp;
   int lvartemp;

   loc = find_func(token); /* find entry point of function */
   if (loc == NULL)
   {
      sntx_err(FUNC_UNDEF); /* function not defined */
   }
   else
   {
      lvartemp = lvartos; /* save local var stack index */
      get_args(); /* get function arguments */
      temp = prog; /* save return location */
      func_push(lvartemp); /* save local var stack index */
      prog = loc; /* reset prog to start of function */
      ret_occurring = 0; /* P the return occurring variable */
      get_params(); /* load the function's parameters with the values of the arguments */
      interp_block(); /* interpret the function */
      ret_occurring = 0; /* clear the return occuring variable */
      prog = temp; /* reset the program pointer */
      lvartos = func_pop();
   }
}

/**
 * \brief Declare a local variable.
 */
void decl_local()
{
   struct var_type i;

   get_token(); /* get type */
   i.v_type = tok;
   i.value = 0; /* init to 0 */
   do /* process comma-separated list */
   {
      get_token(); /* get var name */
      strcpy(i.var_name, token);
      local_push(i);
      get_token();
   } while (*token == ',');

   if (*token != ';')
   {
      sntx_err(SEMI_EXPECTED);
   }
}

/**
 * \brief Push a local variable
 * \param i Variable type
 */
void local_push(struct var_type i)
{
   if (lvartos >= NUM_LOCAL_VARS)
   {
      sntx_err(TOO_MANY_LVARS);
   }
   else
   {
      local_var_stack[lvartos] = i;
      lvartos++;
   }
}

/**
 * \brief Get function parameters
 */
void get_params()
{
   struct var_type *p;
   int i;

   i = lvartos - 1;
   do /* process comma-separated list of parameters */
   {
      get_token();
      p = &local_var_stack[i];
      if (*token != ')')
      {
         if (tok != INT && tok != CHAR)
         {
            sntx_err(TYPE_EXPECTED);
         }

         p->v_type = token_type;
         get_token();

         /* link parameter name with argument already on
            local var stack */
         strcpy(p->var_name, token);
         get_token();
         i--;
      }
      else
      {
         break;
      }
   } while (*token == ',');

   if (*token != ')')
   {
      sntx_err(PAREN_EXPECTED);
   }
}

/**
 * \brief Push the arguments to a function onto the local variable stack
 */
void get_args(void)
{
   int value, count, temp[NUM_PARAMS];
   struct var_type i;

   count = 0;
   get_token();
   if (*token != '(')
   {
      sntx_err(PAREN_EXPECTED);
   }

   /* process a comma-separated list of values */
   do
   {
      eval_exp(&value);
      temp[count] = value; /* save temporarily */
      get_token();
      count++;
   } while (*token == ',');

   count--;
   /* now, push on local_var_stack in reverse order */
   for (; count >= 0; count--)
   {
      i.value = temp[count];
      i.v_type = ARG;
      local_push(i);
   }
}

/**
 * \brief Execute a while loop
 */
void exec_while()
{
   int cond;
   char *temp;

   break_occuring = 0; /* clear the break flag */
   putback();
   temp = prog; /* save location of top of while loop */
   get_token();
   eval_exp(&cond); /* check the conditional expression */
   if (cond)
   {
      interp_block(); /* if true, interpret */
      if (break_occuring > 0)
      {
         break_occuring = 0;
         return;
      }
   }
   else /* otherwise, skip around loop */
   {
      find_eob();
      return;
   }

   prog = temp; /* loop back to top */
}

/**
 * \brief Push index of local variable stack.
 * \param i Index
 */
void func_push(int i)
{
   if (functos >= NUM_FUNC)
   {
      sntx_err(NEST_FUNC);
   }
   else
   {
      call_stack[functos] = i;
      functos++;
   }
}

/**
 * \brief Execute a do loop.
 */
void exec_do()
{
   int cond;
   char *temp;

   putback();
   temp = prog; /* save location of top of do loop */
   break_occuring = 0; /* clear the break flag */

   get_token(); /* get start of loop */
   interp_block(); /* interpret loop */
   if (ret_occurring > 0)
   {
      return;
   }
   if (break_occuring > 0)
   {
      break_occuring = 0;
      return;
   }

   get_token();
   if (tok != WHILE)
   {
      sntx_err(WHILE_EXPECTED);
   }

   eval_exp(&cond); /* check the loop condition */
   if (cond)
   {
      prog = temp; /* if true - loop, otherwise - continue on */
   }
}

/**
 * \brief Execute an if statement
 */
void exec_if()
{
   int cond;

   eval_exp(&cond); /* get if expression */
   if (cond) /* is true so process target of IF */
   {
      interp_block();
   }
   else /* otherwise skip around IF block and process the ELSE, if present */
   {
      find_eob(); /* find start of the next line */
      get_token();

      if (tok != ELSE)
      {
         putback(); /* restore token if no ELSE is present */
         return;
      }

      interp_block();
   }
}

/**
 * \brief Find the end of a block
 */
void find_eob()
{
   int brace;

   get_token();
   brace = 1;
   do
   {
      get_token();
      if (*token == '{')
      {
         brace++;
      }
      else if (*token == '}')
      {
         brace--;
      }
   } while (brace);
}

/**
 * \brief Execute a for loop
 */
void exec_for()
{
   int cond;
   char *temp, *temp2;
   int brace;

   break_occuring = 0; /* clear the break flag */
   get_token();
   eval_exp(&cond); /* initialization expression */
   if (*token != ';')
   {
      sntx_err(SEMI_EXPECTED);
   }

   prog++; /* get past the ';' */
   temp = prog;
   for (;;)
   {
      eval_exp(&cond); /* check the condition */
      if (*token != ';')
      {
         sntx_err(SEMI_EXPECTED);
      }

      prog++; /* get past the ';' */
      temp2 = prog;

      /* find the start of the for block */
      brace = 1;
      while (brace)
      {
         get_token();
         if (*token == '(')
         {
            brace++;
         }

         if (*token == ')')
         {
            brace--;
         }
      }

      if (cond)
      {
         interp_block(); /* if true, interpret */
         if (ret_occurring > 0)
         {
            return;
         }
         if (break_occuring > 0)
         {
            break_occuring = 0;
            return;
         }
      }
      else /* otherwise, skip around loop */
      {
         find_eob();
         return;
      }

      prog = temp2;
      eval_exp(&cond); /* do the increment */
      prog = temp; /* loop back to top */
   }
}
