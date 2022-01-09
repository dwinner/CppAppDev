#include "littlec_parser.h"

/**
 * current location in source code
 */
extern char *prog;

/**
 * points to start of program buffer
 */
extern char *p_buf;

/**
 * hold environment for longjmp()
 */
extern jmp_buf e_buf;

/**
 * string representation of token
 */
extern char token[80];

/**
 * contains type of token
 */
extern char token_type;

/**
 * internal representation of token
 */
extern char tok;

/**
 * function return value
 */
extern int ret_value;

void eval_exp(int *result)
{
   get_token();
   if (!*token)
   {
      sntx_err(NO_EXP);
      return;
   }

   if (*token == ';')
   {
      /* empty expression */
      *result = 0;
      return;
   }

   eval_exp0(result);

   /* return last token read to input stream */
   putback();
}

void eval_exp0(int *value)
{
   /* holds name of var receiving the assignment */
   char temp[ID_LEN];
   register char temp_tok;

   /* if a var, see if assignment */
   if (token_type == IDENTIFIER && is_var(token))
   {
      strcpy_s(temp, ID_LEN, token);
      temp_tok = token_type;
      get_token();
      /* is an assignment */
      if (*token == '=')
      {
         get_token();
         /* get value to assign */
         eval_exp0(value);
         /* assign the value */
         assign_var(temp, *value);
         return;
      }
      else
      {  /* not an assignment */
         /* restore original token */
         putback();
         strcpy_s(token, 80, temp);
         token_type = temp_tok;
      }
   }

   eval_exp1(value);
}

void eval_exp1(int *value)
{
   int partial_value;
   register char op;
   char relops[7] =
       {
           LT,
           LE,
           GT,
           GE,
           EQ,
           NE,
           0
       };

   eval_exp2(value);
   op = *token;
   if (strchr(relops, op))
   {
      get_token();
      eval_exp2(&partial_value);
      /* perform the relational operation */
      switch (op)
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
      }
   }
}

void eval_exp2(int *value)
{
   register char op;
   int partial_value;

   eval_exp3(value);
   while ((op = *token) == '+' || op == '-')
   {
      get_token();
      eval_exp3(&partial_value);
      /* add or subtract */
      switch (op)
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

void eval_exp3(int *value)
{
   register char op;
   int partial_value, t;

   eval_exp4(value);
   while ((op = *token) == '*' || op == '/' || op == '%')
   {
      get_token();
      eval_exp4(&partial_value);
      /* mul, div, or modulus */
      switch (op)
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

void eval_exp5(int *value)
{
   if (*token == '(')
   {
      get_token();
      /* get subexpression */
      eval_exp0(value);
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

void atom(int *value)
{
   int i;

   switch (token_type)
   {
      case IDENTIFIER:
         i = internal_func(token);

         /* call "standard library" function */
         if (i != -1)
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
            /* get var's value */
            *value = find_var(token);
         }

         get_token();
         return;
      case NUMBER: /* is numeric constant */
         *value = atoi(token);
         get_token();
         return;
      case DELIMITER: /* see if character constant */
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
            /* process empty expression */
            return;
         }
         else
         {
            /* syntax error */
            sntx_err(SYNTAX);
         }
      default:
         /* syntax error */
         sntx_err(SYNTAX);
   }
}

void sntx_err(int error)
{
   char *p, *temp;
   int line_count = 0;
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
   while (p != prog && *p != '\0')
   {
      /* find line number of error */
      p++;
      if (*p == '\r')
      {
         line_count++;
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
         line_count++;
      }
      else if (*p == '\0')
      {
         line_count++;
      }
   }

   printf(" in line %d\n", line_count);

   temp = p--;
   for (i = 0; i < 20 && p > p_buf && *p != '\n' && *p != '\r'; i++, p--)
   {}

   for (i = 0; i < 30 && p <= temp; i++, p++)
   {
      printf("%c", *p);
   }

   /* return to safe point */
   longjmp(e_buf, 1);
}

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

   /* Handle Windows and Mac newlines */
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

   /* Handle Unix newlines */
   if (*prog == '\n')
   {
      ++prog;

      /* skip over white space */
      while (iswhite(*prog) && *prog)
      {
         ++prog;
      }
   }

   /* end of file */
   if (*prog == '\0')
   {
      *token = '\0';
      tok = FINISHED;

      return (token_type = DELIMITER);
   }

   /* block delimiters */
   if (strchr("{}", *prog))
   {
      *temp = *prog;
      temp++;
      *temp = '\0';
      prog++;

      return (token_type = BLOCK);
   }

   /* look for comments */
   if (*prog == '/' && *(prog + 1) == '*')
   {
      /* is a comment */
      prog += 2;
      do
      {
         /* find end of comment */
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
      }
      while (*prog != '/');

      prog++;
   }

   /* look for C++ style comments */
   if (*prog == '/' && *(prog + 1) == '/')   /* is a comment */
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
      /* end of file */
      *token = '\0';
      tok = FINISHED;

      return (token_type = DELIMITER);
   }

   if (strchr("!<>=", *prog))
   {
      /* is or might be a relational operator */
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
         return (token_type = DELIMITER);
      }
   }

   /* delimiter */
   if (strchr("+-*^/%=;(),'", *prog))
   {
      *temp = *prog;
      prog++; /* advance to next position */
      temp++;
      *temp = '\0';

      return (token_type = DELIMITER);
   }

   /* quoted string */
   if (*prog == '"')
   {
      prog++;
      while ((*prog != '"' && *prog != '\r' && *prog != '\n' && *prog != '\0') ||
             (*prog == '"' && *(prog - 1) == '\\'))
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

   /* number */
   if (isdigit((int) *prog))
   {
      while (!isdelim(*prog))
      {
         *temp++ = *prog++;
      }

      *temp = '\0';
      return (token_type = NUMBER);
   }

   /* var or command */
   if (isalpha((int) *prog))
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
      /* convert to internal rep */
      tok = look_up(token);
      token_type = tok ? KEYWORD : IDENTIFIER;
   }

   return token_type;
}
