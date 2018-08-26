/**
 * Recursive descent parser for integer expressions
 * which may include variables and function calls.
 */

#include "parser.h"
#include "littlec.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * An array of these structures will hold the
 * info associated with global variables.
 */
//extern VariableType global_vars[NUM_GLOBAL_VARS];

/**
 * Function call stack
 */
extern struct func_type func_stack[NUM_FUNC];

/**
 * \brief Keyword table
 */
//extern struct commands table[];

/**
 * \brief Process an assignment expression
 * \param value Value to parse
 */
void eval_exp0(int *value)
{
   char temp[ID_LEN]; /* holds name of var receiving the assignment */
   register char temp_tok;

   if (token_type == IDENTIFIER)
   {
      if (is_var(token)) /* if a var, see if assignment */
      {
         strcpy(temp, token);
         temp_tok = token_type;
         get_token();
         if (*token == '=') /* is an assignment */
         {
            get_token();
            eval_exp0(value); /* get value to assign */
            assign_var(temp, *value); /* assign the value */
            return;
         }
         /* not an assignment */
         putback(); /* restore original token */
         strcpy(token, temp);
         token_type = temp_tok;
      }
   }

   eval_exp1(value);
}

/**
 * \brief Entry point to parser
 * \param value Value to parse
 */
void eval_exp(int *value)
{
   get_token();
   if (!*token)
   {
      sntx_err(NO_EXP);
      return;
   }

   if (*token == ';')
   {
      *value = 0; /* empty expression */
      return;
   }

   eval_exp0(value);
   putback(); /* return last token read to input stream */
}

/**
 * \brief Process relational operators
 * \param value Value to process
 */
void eval_exp1(int *value)
{
   int partial_value;
   register char op;
   char relops[7] = {LT, LE, GT, GE, EQ, NE, 0};

   eval_exp2(value);
   op = *token;
   if (strchr(relops, op))
   {
      get_token();
      eval_exp2(&partial_value);
      switch (op) /* perform the relational operation */
      {
         case LT:
            *value = *value < partial_value;
            break;
         case LE:
            *value = *value <= partial_value;
            break;
         case GT:
            *value = *value > partial_value;
            break;
         case GE:
            *value = *value >= partial_value;
            break;
         case EQ:
            *value = *value == partial_value;
            break;
         case NE:
            *value = *value != partial_value;
            break;
         default:
            break;
      }
   }
}

/**
 * \brief Add or subtract two terms
 * \param value Value to process
 */
void eval_exp2(int *value)
{
   register char op;
   int partial_value;

   eval_exp3(value);
   op = *token;
   while (op == '+' || op == '-')
   {
      get_token();
      eval_exp3(&partial_value);
      switch (op) /* Add or subtract */
      {
         case '-':
            *value = *value - partial_value;
            break;
         case '+':
            *value = *value + partial_value;
            break;
      }
   }
}

/**
 * \brief Multiply or divide two factors
 * \param value Value to parse
 */
void eval_exp3(int *value)
{
   register char op;
   int partial_value, t;

   eval_exp4(value);
   op = *token;
   while (op == '*' || op == '/' || op == '%')
   {
      get_token();
      eval_exp4(&partial_value);
      switch (op) /* mul, div, or modulus */
      {
         case '*':
            *value = *value * partial_value;
            break;
         case '/':
            if (partial_value == 0)
            {
               sntx_err(DIV_BY_ZERO);
            }

            *value = (*value) / partial_value;
            break;
         case '%':
            t = (*value) / partial_value;
            *value = *value - (t * partial_value);
            break;
      }
   }
}

/**
 * \brief Is unary '+' or '-' token
 * \param value Value to parse
 */
void eval_exp4(int *value)
{
   register char op;

   op = '\0';
   if (*token == '+' || *token == '-')
   {
      op = *token;
      get_token();
   }

   eval_exp5(value);
   if (op && op == '-')
   {
      *value = -(*value);
   }
}

/**
 * \brief Process parenthesized expression
 * \param value Value to parse
 */
void eval_exp5(int *value)
{
   if (*token == '(')
   {
      get_token();
      eval_exp0(value); /* get subexpression */
      if (*token != ')')
      {
         sntx_err(PAREN_EXPECTED);
      }

      get_token();
   }
   else
   {
      atom(value);
   }
}

/**
 * \brief Find value of number, variable, or function
 * \param value Value to parse
 */
void atom(int *value)
{
   int i;

   switch (token_type)
   {
      case IDENTIFIER:
         i = internal_func(token);
         if (i != -1) /* call "standart library" function */
         {
            *value = (*intern_func[i].p)();
         }
         else if (find_func(token)) /* call user-defined function */
         {
            call();
            *value = ret_value;
         }
         else
         {
            *value = find_var(token); /* get var's value */
         }

         get_token();
         return;
      case NUMBER: /* is numeric constant */
         *value = atoi(token);
         get_token();
         return;
      case DELIMETER: /* see if character constant */
         if (*token == '\'')
         {
            *value = *prog;
            prog++;
            if (*prog != '\'')
            {
               sntx_err(QUOTE_EXPECTED);
            }

            prog++;
            get_token();
            return;
         }

         if (*token == ')')
         {
            return; /* process empty expression */
         }
         sntx_err(SYNTAX); /* syntax error */
         break;
      default:
         sntx_err(SYNTAX); /* syntax error */
   }
}

/**
 * \brief Display an error message
 * \param error Error number
 */
void sntx_err(int error)
{
   char *p, *temp;
   int linecount = 0;
   register int i;

   static char *e[] =
      {
         "syntax error",
         "unbalanced parentheses",
         "no expression present",
         "equals sign expected",
         "not a variable",
         "parameter error",
         "semicolon expected",
         "unbalanced braces",
         "function undefined",
         "type specifier expected",
         "too many nested function calls",
         "return without call",
         "parentheses expected",
         "while expected",
         "closing quote expected",
         "not a string",
         "too many local variables",
         "division by zero"
      };

   printf("\n%s", e[error]);
   p = p_buf;
   while (p != prog && *p != '\0') /* find line number of error */
   {
      p++;
      if (*p == '\r')
      {
         linecount++;
         if (p == prog)
         {
            break;
         }

         /* See if this is a Windows or Mac newline */
         p++;
         /* If we are a mac, backtrack */
         if (*p != '\n')
         {
            p--;
         }
      }
      else if (*p == '\n')
      {
         linecount++;
      }
      else if (*p == '\0')
      {
         linecount++;
      }
   }

   printf(" in line %d\n", linecount);
   temp = p--;
   for (i = 0; i < 20 && p > p_buf && *p != '\n' && *p != '\r'; i++, p--)
   {
   }

   for (i = 0; i < 30 && p <= temp; i++, p++)
   {
      printf("%c", *p);
   }

   longjmp(e_buf, 1); /* return to safe point */
}

/**
 * \brief Find the location of all functions in the program
 *        and store global variables.
 */
void prescan()
{
   char *p, *tp;
   char temp[ID_LEN + 1];
   int datatype;
   int brace = 0; /* When 0, this var tells us that current
                     source position is outside of any function. */
   p = prog;
   func_index = 0;
   do
   {
      while (brace) /* bypass code inside functions */
      {
         get_token();
         if (*token == '{')
         {
            brace++;
         }

         if (*token == '}')
         {
            brace--;
         }
      }

      tp = prog; /* save current position */
      get_token();
      /* global var type or function return type */
      if (tok == CHAR || tok == INT)
      {
         datatype = tok; /* save data type */
         get_token();
         if (token_type == IDENTIFIER)
         {
            strcpy(temp, token);
            get_token();
            if (*token != '(') /* must be global var */
            {
               prog = tp; /* return to start of declaration */
               decl_global();
            }
            else if (*token == '(') /* must be a function */
            {
               func_table[func_index].loc = prog;
               func_table[func_index].ret_type = datatype;
               strcpy(func_table[func_index].func_name, temp);
               func_index++;
               while (*prog != ')')
               {
                  prog++;
               }

               prog++;
               /* now prog points to opening curly brace of function */
            }
            else
            {
               putback();
            }
         }
         else if (*token == '{')
         {
            brace++;
         }
      }
   } while (tok != FINISHED);

   prog = p;
}

/**
 * \brief Return a token to input stream
 */
void putback()
{
   char *t;
   t = token;
   for (; *t; t++)
   {
      prog--;
   }
}

/**
 * \brief Checks whether c is delimeter or not
 * \param c Char to be checked
 * \return True if c is a delimeter, False - otherwise
 */
int isdelim(char c)
{
   return strchr(" !;,+-<>'/*%^=()", c) || c == 9 || c == '\r' || c == '\n' || c == 0
          ? 1
          : 0;
}

/**
 * \brief Returns 1 if c is space or tab
 * \param c Char to be checked
 * \return 1 if c is space or tab
 */
int iswhite(char c)
{
   return c == ' ' || c == '\t' ? 1 : 0;
}

/**
 * \brief Return index of internal library function or -1 if nothing's been found
 * \param s The function name
 * \return Found index or -1 if nothing's been found
 */
int internal_func(char *s)
{
   int i = -1;

   for (i = 0; i < intern_func[i].f_name[0]; i++)
   {
      if (!strcmp(intern_func[i].f_name, s))
      {
         break;
      }
   }

   return i;
}

/**
 * \brief Looks up a token's internal representation in the token table
 * \param s Token to be looked up
 * \return Found token or 0 if nothing has been found
 */
char look_up(char *s)
{
   register int i;
   char *p;
   char foundToken = 0; /* unknown command */

   /* convert to lower case */
   p = s;
   while (*p)
   {
      *p = (char) tolower(*p);
      p++;
   }

   /* see if token is in table */
   for (i = 0; *table[i].command; i++)
   {
      if (!strcmp(table[i].command, s))
      {
         foundToken = table[i].tok;
         break;
      }
   }

   return foundToken;
}

/**
 * \brief Find the function by name
 * \param name The function name
 * \return The entry point of the specified function, NULL - if not found
 */
char *find_func(char *name)
{
   char *location = NULL;

   for (register int i = 0; i < func_index; i++)
   {
      if (!strcmp(name, func_table[i].func_name))
      {
         char *t = func_table[i].loc;
         break;
      }
   }

   return location;
}

/**
 * \brief Get a token
 * \return Consumed token char
 */
char get_token(void)
{
   register char *temp;
   token_type = 0;
   tok = 0;
   temp = token;
   *temp = '\0';

   /* skip over white space */
   while (iswhite(*prog) && *prog)
   {
      ++prog;
   }

   /* Handle windows and mac new lines */
   if (*prog == '\r')
   {
      ++prog;

      /* Only skip \n if it exists (if it doesn't, we are running on mac) */
      if (*prog == '\n')
      {
         ++prog;
      }

      /* skip over white space */
      while (iswhite(*prog) && *prog)
      {
         ++prog;
      }
   }

   /* Handle Unix new lines */
   if (*prog == '\n')
   {
      ++prog;

      /* skip over white space */
      while (iswhite(*prog) && *prog)
      {
         ++prog;
      }
   }

   if (*prog == '\0') /* end of file */
   {
      *token = '\0';
      tok = FINISHED;
      return (token_type == DELIMETER);
   }

   if (strchr("{}", *prog)) /* block delimeters */
   {
      *temp = *prog;
      temp++;
      *temp = '\0';
      prog++;
      return (token_type == BLOCK);
   }

   /* look for comments */
   if (*prog == '/' && *(prog + 1) == '*')
   {
      prog += 2;
      do /* find end of comment */
      {
         while (*prog != '*' && *prog != '\0')
         {
            prog++;
         }

         if (*prog == '\0')
         {
            prog--;
            break;
         }

         prog++;
      } while (*prog != '/');

      prog++;
   }

   /* look for C++ style comments */
   if (*prog == '/' && *(prog + 1) == '/')
   {
      prog += 2;

      /* find end of line */
      while (*prog != '\r' && *prog != '\n' && *prog != '\0')
      {
         prog++;
      }

      if (*prog == '\r' && *(prog + 1) == '\n')
      {
         prog++;
      }
   }

   /* look for the end of file after a comment */
   if (*prog == '\0')
   {
      *token = '\0';
      tok = FINISHED;
      return (token_type == DELIMETER);
   }

   if (strchr("!<>=", *prog)) /* is or might be a relational operator */
   {
      switch (*prog)
      {
         case '=':
            if (*(prog + 1) == '=')
            {
               prog++;
               prog++;
               *temp = EQ;
               temp++;
               *temp = EQ;
               temp++;
               *temp = '\0';
            }

            break;
         case '!':
            if (*(prog + 1) == '=')
            {
               prog++;
               prog++;
               *temp = NE;
               temp++;
               *temp = NE;
               temp++;
               *temp = '\0';
            }

            break;
         case '<':
            if (*(prog + 1) == '=')
            {
               prog++;
               prog++;
               *temp = LE;
               temp++;
               *temp = LE;
            }
            else
            {
               prog++;
               *temp = LT;
            }

            temp++;
            *temp = '\0';
            break;
         case '>':
            if (*(prog + 1) == '=')
            {
               prog++;
               prog++;
               *temp = GE;
               temp++;
               *temp = GE;
            }
            else
            {
               prog++;
               *temp = GT;
            }

            temp++;
            *temp = '\0';
            break;
      }

      if (*token)
      {
         return (token_type = DELIMETER);
      }
   }

   if (strchr("+-*^/%=;(),'", *prog)) /* delimeter */
   {
      *temp = *prog;
      prog++; /* advance to the next position */
      temp++;
      *temp = '\0';
      return (token_type = DELIMETER);
   }

   if (*prog == '"') /* quoted string */
   {
      prog++;
      while ((*prog != '"' && *prog != '\r' && *prog != '\n' && *prog != '\0')
             || (*prog == '"' && *(prog - 1) == '\\'))
      {
         *temp++ = *prog++;
      }

      if (*prog == '\r' || *prog == '\n' || *prog == '\0')
      {
         sntx_err(SYNTAX);
      }

      prog++;
      *temp = '\0';

      str_replace(token, "\\a", "\a");
      str_replace(token, "\\b", "\b");
      str_replace(token, "\\f", "\f");
      str_replace(token, "\\n", "\n");
      str_replace(token, "\\r", "\r");
      str_replace(token, "\\t", "\t");
      str_replace(token, "\\v", "\v");
      str_replace(token, "\\\\", "\\");
      str_replace(token, "\\\'", "\'");
      str_replace(token, "\\\"", "\"");
      return (token_type = STRING);
   }

   if (isdigit((int) *prog)) /* number */
   {
      while (!isdelim(*prog))
      {
         *temp++ = *prog++;
      }

      *temp = '\0';
      return (token_type = NUMBER);
   }

   if (isalpha((int) *prog)) /* var or command */
   {
      while (!isdelim(*prog))
      {
         *temp++ = *prog++;
      }

      token_type = TEMP;
   }

   *temp = '\0';

   /* see if a string is a command or a variable */
   if (token_type == TEMP)
   {
      tok = look_up(token); /* convert to internal representation */
      token_type = tok ? KEYWORD : IDENTIFIER;
   }

   return token_type;
}

/**
 * \brief   An in-place modification find and replace of the string.
 *          Assumes the buffer pointed to by line is large enough
 *          to hold the resulting string
 * \param line    Source line
 * \param search  String to search
 * \param replace String for replacement
 */
static void str_replace(char *line, const char *search, const char *replace)
{
   char *sp;
   while ((sp = strstr(line, search)) != NULL)
   {
      int search_len = (int) strlen(search);
      int replace_len = (int) strlen(replace);
      int tail_len = (int) strlen(sp + search_len);

      memmove(sp + replace_len, sp + search_len, tail_len + 1);
      memcpy(sp, replace, replace_len);
   }
}
