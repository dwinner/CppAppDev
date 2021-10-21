listing 1
/* Get a token. */
int get_token(void)
{

  register char *temp;

  token_type = 0; tok = 0;

  temp = token;
  *temp = '\0';

  /* skip over white space */
  while(iswhite(*prog) && *prog) ++prog;

  if(*prog == '\r') {
    ++prog;
    ++prog;
    /* skip over white space */
    while(iswhite(*prog) && *prog) ++prog;
  }

  if(*prog == '\0') { /* end of file */
    *token = '\0';
    tok = FINISHED;
    return (token_type = DELIMITER);
  }

  if(strchr("{}", *prog)) { /* block delimiters */
    *temp = *prog;
    temp++;
    *temp = '\0';
    prog++;
    return (token_type = BLOCK);
  }

  /* look for comments */
  if(*prog == '/')
    if(*(prog+1) == '*') { /* is a comment */
      prog += 2;
      do { /* find end of comment */
        while(*prog != '*') prog++;
        prog++;
      } while (*prog != '/');
      prog++;
    }

  if(strchr("!<>=", *prog)) { /* is or might be
                                 a relational operator */
    switch(*prog) {
      case '=': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = EQ;
          temp++; *temp = EQ; temp++;
          *temp = '\0';
       }
       break;
      case '!': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = NE;
          temp++; *temp = NE; temp++;
          *temp = '\0';
       }
       break;
      case '<': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = LE; temp++; *temp = LE;
       }
       else {
          prog++;
          *temp = LT;
       }
       temp++;
       *temp = '\0';
       break;
      case '>': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = GE; temp++; *temp = GE;
       }
       else {
         prog++;
         *temp = GT;
       }
       temp++;
       *temp = '\0';
       break;
    }
    if(*token) return (token_type = DELIMITER);
  }

  if(strchr("+-*^/%=;(),'", *prog)){ /* delimiter */
    *temp = *prog;
    prog++; /* advance to next position */
    temp++;
    *temp = '\0';
    return (token_type = DELIMITER);
  }

  if(*prog=='"') { /* quoted string */
    prog++;
    while(*prog != '"'&& *prog != '\r') *temp++ = *prog++;
    if(*prog == '\r') sntx_err(SYNTAX);
    prog++; *temp = '\0';
    return (token_type = STRING);
  }

  if(isdigit(*prog)) { /* number */
    while(!isdelim(*prog)) *temp++ = *prog++;
    *temp = '\0';
    return (token_type = NUMBER);
  }

  if(isalpha(*prog)) { /* var or command */
    while(!isdelim(*prog)) *temp++ = *prog++;
    token_type = TEMP;
  }

  *temp = '\0';

  /* see if a string is a command or a variable */
  if(token_type==TEMP) {
    tok = look_up(token); /* convert to internal rep */
    if(tok) token_type = KEYWORD; /* is a keyword */
    else token_type = IDENTIFIER;
  }
  return token_type;
}

listing 3
/* Recursive descent parser for integer expressions
   which may include variables and function calls.
*/
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* An array of these structures will hold the info
   associated with global variables.
*/
extern struct var_type {
  char var_name[32];
  int v_type;
  int value;
}  global_vars[NUM_GLOBAL_VARS];

/*  This is the function call stack. */
extern struct func_type {
  char func_name[32];
  int ret_type; 
  char *loc;  /* location of function entry point in file */
} func_stack[NUM_FUNC];

/* Keyword table */
extern struct commands {
  char command[20];
  char tok;
} table[];

/* "Standard library" functions are declared here so
   they can be put into the internal function table that
   follows.
 */
int call_getche(void), call_putch(void);
int call_puts(void), print(void), getnum(void);

struct intern_func_type {
  char *f_name; /* function name */
  int (*p)();   /* pointer to the function */
} intern_func[] = {
  "getche", call_getche,
  "putch", call_putch,
  "puts", call_puts,
  "print", print,
  "getnum", getnum,
  "", 0  /* null terminate the list */
};

extern char token[80]; /* string representation of token */
extern char token_type; /* contains type of token */
extern char tok; /* internal representation of token */

extern int ret_value; /* function return value */

void eval_exp0(int *value);
void eval_exp(int *value);
void eval_exp1(int *value);
void eval_exp2(int *value);
void eval_exp3(int *value);
void eval_exp4(int *value);
void eval_exp5(int *value);
void atom(int *value);
void sntx_err(int error), putback(void);
void assign_var(char *var_name, int value);
int isdelim(char c), look_up(char *s), iswhite(char c);
int find_var(char *s), get_token(void);
int internal_func(char *s);
int is_var(char *s);
char *find_func(char *name);
void call(void);

/* Entry point into parser. */
void eval_exp(int *value)
{
  get_token();
  if(!*token) {
    sntx_err(NO_EXP);
    return;
  }
  if(*token == ';') {
    *value = 0; /* empty expression */
    return;
  }
  eval_exp0(value);
  putback(); /* return last token read to input stream */
}

/* Process an assignment expression */
void eval_exp0(int *value)
{
  char temp[ID_LEN];  /* holds name of var receiving
                         the assignment */
  register int temp_tok;

  if(token_type == IDENTIFIER) {
    if(is_var(token)) {  /* if a var, see if assignment */
      strcpy(temp, token);
      temp_tok = token_type;
      get_token();
      if(*token == '=') {  /* is an assignment */
        get_token();
        eval_exp0(value);  /* get value to assign */
        assign_var(temp, *value);  /* assign the value */
        return;
      }
      else {  /* not an assignment */
        putback();  /* restore original token */
        strcpy(token, temp);
        token_type = temp_tok;
      }
    }
  }
  eval_exp1(value);
}

/* Process relational operators. */
void eval_exp1(int *value)
{
  int partial_value;
  register char op;
  char relops[7] = {
    LT, LE, GT, GE, EQ, NE, 0
  };

  eval_exp2(value);
  op = *token;
  if(strchr(relops, op)) {
    get_token();
    eval_exp2(&partial_value);
    switch(op) {  /* perform the relational operation */
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

/*  Add or subtract two terms. */
void eval_exp2(int *value)
{
  register char  op;
  int partial_value;

  eval_exp3(value);
  while((op = *token) == '+' || op == '-') {
    get_token();
    eval_exp3(&partial_value);
    switch(op) { /* add or subtract */
      case '-':
        *value = *value - partial_value;
        break;
      case '+':
        *value = *value + partial_value;
        break;
    }
  }
}

/* Multiply or divide two factors. */
void eval_exp3(int *value)
{
  register char  op;
  int partial_value, t;

  eval_exp4(value);
  while((op = *token) == '*' || op == '/' || op == '%') {
    get_token();
    eval_exp4(&partial_value);
    switch(op) { /* mul, div, or modulus */
      case '*':
        *value = *value * partial_value;
        break;
      case '/':
        if(partial_value == 0) sntx_err(DIV_BY_ZERO);       
        *value = (*value) / partial_value;
        break;
      case '%':
        t = (*value) / partial_value;
        *value = *value-(t * partial_value);
        break;
    }
  }
}

/* Is a unary + or -. */
void eval_exp4(int *value)
{
  register char  op;

  op = '\0';
  if(*token == '+' || *token == '-') {
    op = *token;
    get_token();
  }
  eval_exp5(value);
  if(op)
    if(op == '-') *value = -(*value);
}

/* Process parenthesized expression. */
void eval_exp5(int *value)
{
  if((*token == '(')) {
    get_token();
    eval_exp0(value);   /* get subexpression */
    if(*token != ')') sntx_err(PAREN_EXPECTED);
    get_token();
  }
  else
    atom(value);
}

/* Find value of number, variable, or function. */
void atom(int *value)
{
  int i;

  switch(token_type) {
  case IDENTIFIER:
    i = internal_func(token);
    if(i!= -1) {  /* call "standard library" function */
      *value = (*intern_func[i].p)();
    }
    else
    if(find_func(token)) { /* call user-defined function */
      call();
      *value = ret_value;
    }
    else *value = find_var(token); /* get var's value */
    get_token();
    return;
  case NUMBER: /* is numeric constant */
    *value = atoi(token);
    get_token();
    return;
  case DELIMITER: /* see if character constant */
    if(*token == '\'') {
      *value = *prog;
      prog++;
      if(*prog!='\'') sntx_err(QUOTE_EXPECTED);
      prog++;
      get_token();
      return ;
    }
    if(*token==')') return; /* process empty expression */
    else sntx_err(SYNTAX); /* syntax error */
  default:
    sntx_err(SYNTAX); /* syntax error */
  }
}

/* Display an error message. */
void sntx_err(int error)
{
  char *p, *temp;
  int linecount = 0;
  register int i;

  static char *e[]= {
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
  while(p != prog) {  /* find line number of error */
    p++;
    if(*p == '\r') {
      linecount++;
    }
  }
  printf(" in line %d\n", linecount);

  temp = p;
  for(i=0; i < 20 && p > p_buf && *p != '\n'; i++, p--);
  for(i=0; i < 30 && p <= temp; i++, p++) printf("%c", *p);

  longjmp(e_buf, 1); /* return to safe point */
}

/* Get a token. */
int get_token(void)
{

  register char *temp;

  token_type = 0; tok = 0;

  temp = token;
  *temp = '\0';

  /* skip over white space */
  while(iswhite(*prog) && *prog) ++prog;

  if(*prog == '\r') {
    ++prog;
    ++prog;
    /* skip over white space */
    while(iswhite(*prog) && *prog) ++prog;
  }

  if(*prog == '\0') { /* end of file */
    *token = '\0';
    tok = FINISHED;
    return (token_type = DELIMITER);
  }

  if(strchr("{}", *prog)) { /* block delimiters */
    *temp = *prog;
    temp++;
    *temp = '\0';
    prog++;
    return (token_type = BLOCK);
  }

  /* look for comments */
  if(*prog == '/')
    if(*(prog+1) == '*') { /* is a comment */
      prog += 2;
      do { /* find end of comment */
        while(*prog != '*') prog++;
        prog++;
      } while (*prog != '/');
      prog++;
    }

  if(strchr("!<>=", *prog)) { /* is or might be
                                 a relational operator */
    switch(*prog) {
      case '=': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = EQ;
          temp++; *temp = EQ; temp++;
          *temp = '\0';
       }
       break;
      case '!': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = NE;
          temp++; *temp = NE; temp++;
          *temp = '\0';
       }
       break;
      case '<': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = LE; temp++; *temp = LE;
       }
       else {
          prog++;
          *temp = LT;
       }
       temp++;
       *temp = '\0';
       break;
      case '>': if(*(prog+1) == '=') {
          prog++; prog++;
          *temp = GE; temp++; *temp = GE;
       }
       else {
         prog++;
         *temp = GT;
       }
       temp++;
       *temp = '\0';
       break;
    }
    if(*token) return(token_type = DELIMITER);
  }

  if(strchr("+-*^/%=;(),'", *prog)){ /* delimiter */
    *temp = *prog;
    prog++; /* advance to next position */
    temp++;
    *temp = '\0';
    return (token_type = DELIMITER);
  }

  if(*prog=='"') { /* quoted string */
    prog++;
    while(*prog != '"'&& *prog != '\r') *temp++ = *prog++;
    if(*prog == '\r') sntx_err(SYNTAX);
    prog++; *temp = '\0';
    return (token_type = STRING);
  }

  if(isdigit(*prog)) { /* number */
    while(!isdelim(*prog)) *temp++ = *prog++;
    *temp = '\0';
    return (token_type = NUMBER);
  }

  if(isalpha(*prog)) { /* var or command */
    while(!isdelim(*prog)) *temp++ = *prog++;
    token_type = TEMP;
  }

  *temp = '\0';

  /* see if a string is a command or a variable */
  if(token_type==TEMP) {
    tok = look_up(token); /* convert to internal rep */
    if(tok) token_type = KEYWORD; /* is a keyword */
    else token_type = IDENTIFIER;
  }
  return token_type;
}

/* Return a token to input stream. */
void putback(void)
{
  char *t;

  t = token;
  for(; *t; t++) prog--;
}

/* Look up a token's internal representation in the
   token table.
*/
int look_up(char *s)
{
  register int i;
  char *p;

  /* convert to lowercase */
  p = s;
  while(*p) { *p = tolower(*p); p++; }

  /* see if token is in table */
  for(i=0; *table[i].command; i++) {
    if(!strcmp(table[i].command, s)) return table[i].tok;
  }
  return 0; /* unknown command */
}

/* Return index of internal library function or -1 if
   not found.
*/
int internal_func(char *s)
{
  int i;

  for(i=0; intern_func[i].f_name[0]; i++) {
    if(!strcmp(intern_func[i].f_name, s))  return i;
  }
  return -1;
}

/* Return true if c is a delimiter. */
int isdelim(char c)
{
  if(strchr(" !;,+-<>'/*%^=()", c) || c == 9 ||
     c == '\r' || c == 0) return 1;
  return 0;
}

/* Return 1 if c is space or tab. */
int iswhite(char c)
{
  if(c == ' ' || c == '\t') return 1;
  else return 0;
}


listing 4
/* "Standard library" functions are declared here so
   they can be put into the internal function table that
   follows.
 */
int call_getche(void), call_putch(void);
int call_puts(void), print(void), getnum(void);

struct intern_func_type {
  char *f_name; /* function name */
  int (*p)();   /* pointer to the function */
} intern_func[] = {
  "getche", call_getche,
  "putch", call_putch,
  "puts", call_puts,
  "print", print,
  "getnum", getnum,
  "", 0  /* null terminate the list */
};

listing 5
/* Find the location of all functions in the program
   and store global variables. */
void prescan(void)
{
  char *p, *tp;
  char temp[32];
  int datatype; 
  int brace = 0;  /* When 0, this var tells us that
                     current source position is outside
                     of any function. */

  p = prog;
  func_index = 0;
  do {
    while(brace) {  /* bypass code inside functions */
      get_token();
      if(*token == '{') brace++;
      if(*token == '}') brace--;
    }

    tp = prog; /* save current position */
    get_token();
    /* global var type or function return type */
    if(tok==CHAR || tok==INT) { 
      datatype = tok; /* save data type */
      get_token();
      if(token_type == IDENTIFIER) {
        strcpy(temp, token);
        get_token();
        if(*token != '(') { /* must be global var */
          prog = tp; /* return to start of declaration */
          decl_global();
        }
        else if(*token == '(') {  /* must be a function */
          func_table[func_index].loc = prog;
          func_table[func_index].ret_type = datatype;
          strcpy(func_table[func_index].func_name, temp);
          func_index++;
          while(*prog != ')') prog++;
          prog++;
          /* now prog points to opening curly 
             brace of function */
        }
        else putback();
      }
    }
    else if(*token == '{') brace++;
  } while(tok != FINISHED);
  prog = p;
}

listing 6
/* An array of these structures will hold the info
   associated with global variables.
*/
struct var_type {
  char var_name[ID_LEN];
  int v_type;
  int value;
}  global_vars[NUM_GLOBAL_VARS];

int gvar_index; /* index into global variable table */

/* Declare a global variable. */
void decl_global(void)
{
  int vartype;

  get_token();  /* get type */

  vartype = tok; /* save var type */

  do { /* process comma-separated list */
    global_vars[gvar_index].v_type = vartype;
    global_vars[gvar_index].value = 0;  /* init to 0 */
    get_token();  /* get name */
    strcpy(global_vars[gvar_index].var_name, token);
    get_token();
    gvar_index++;
  } while(*token == ',');
  if(*token != ';') sntx_err(SEMI_EXPECTED);
}

listing 7
int main(int argc, char *argv[])
{
  if(argc != 2) {
    printf("Usage: littlec <filename>\n");
    exit(1);
  }

  /* allocate memory for the program */
  if((p_buf = (char *) malloc(PROG_SIZE))==NULL) {
    printf("Allocation Failure");
    exit(1);
  }

  /* load the program to execute */
  if(!load_program(p_buf, argv[1])) exit(1);
  if(setjmp(e_buf)) exit(1); /* initialize long jump buffer */

  gvar_index = 0;  /* initialize global variable index */

  /* set program pointer to start of program buffer */
  prog = p_buf;
  prescan(); /* find the location of all functions
                and global variables in the program */

  lvartos = 0;     /* initialize local variable stack index */
  functos = 0;     /* initialize the CALL stack index */

  /* setup call to main() */
  prog = find_func("main"); /* find program starting point */

  if(!prog) { /* incorrect or missing main() function in program */
    printf("main() not found.\n");
    exit(1);
  }

  prog--; /* back up to opening ( */
  strcpy(token, "main");
  call(); /* call main() to start interpreting */

  return 0;
}

listing 8
/* Interpret a single statement or block of code. When
   interp_block() returns from its initial call, the final
   brace (or a return) in main() has been encountered.
*/
void interp_block(void)
{
  int value;
  char block = 0;

  do {
    token_type = get_token();

    /* If interpreting single statement, return on
       first semicolon.
    */

    /* see what kind of token is up */
    if(token_type == IDENTIFIER) {
      /* Not a keyword, so process expression. */
      putback();  /* restore token to input stream for
                     further processing by eval_exp() */
      eval_exp(&value);  /* process the expression */
      if(*token!=';') sntx_err(SEMI_EXPECTED);
    }
    else if(token_type==BLOCK) { /* if block delimiter */
      if(*token == '{') /* is a block */
        block = 1; /* interpreting block, not statement */
      else return; /* is a }, so return */
    }
    else /* is keyword */
      switch(tok) {
        case CHAR:
        case INT:     /* declare local variables */
          putback();
          decl_local();
          break;
        case RETURN:  /* return from function call */
          func_ret();
          return;
        case IF:      /* process an if statement */
          exec_if();
          break;
        case ELSE:    /* process an else statement */
          find_eob(); /* find end of else block
                         and continue execution */
          break;
        case WHILE:   /* process a while loop */
          exec_while();
          break;
        case DO:      /* process a do-while loop */
          exec_do();
          break;
        case FOR:     /* process a for loop */
          exec_for();
          break;
        case END:
          exit(0);
      }
  } while (tok != FINISHED && block);
}

listing 9
/* A Little C interpreter. */

#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUM_FUNC        100
#define NUM_GLOBAL_VARS 100
#define NUM_LOCAL_VARS  200
#define NUM_BLOCK       100
#define ID_LEN          31
#define FUNC_CALLS      31
#define NUM_PARAMS      31
#define PROG_SIZE       10000
#define LOOP_NEST       31

enum tok_types {DELIMITER, IDENTIFIER, NUMBER, KEYWORD,
                TEMP, STRING, BLOCK};

/* add additional C keyword tokens here */
enum tokens {ARG, CHAR, INT, IF, ELSE, FOR, DO, WHILE,
             SWITCH, RETURN, EOL, FINISHED, END};

/* add additional double operators here (such as ->) */
enum double_ops {LT=1, LE, GT, GE, EQ, NE};

/* These are the constants used to call sntx_err() when
   a syntax error occurs. Add more if you like.
   NOTE: SYNTAX is a generic error message used when
   nothing else seems appropriate.
*/
enum error_msg
     {SYNTAX, UNBAL_PARENS, NO_EXP, EQUALS_EXPECTED,
      NOT_VAR, PARAM_ERR, SEMI_EXPECTED,
      UNBAL_BRACES, FUNC_UNDEF, TYPE_EXPECTED,
      NEST_FUNC, RET_NOCALL, PAREN_EXPECTED,
      WHILE_EXPECTED, QUOTE_EXPECTED, NOT_TEMP,
      TOO_MANY_LVARS, DIV_BY_ZERO};

char *prog;    /* current location in source code */
char *p_buf;   /* points to start of program buffer */
jmp_buf e_buf; /* hold environment for longjmp() */

/* An array of these structures will hold the info
   associated with global variables.
*/
struct var_type {
  char var_name[ID_LEN];
  int v_type;
  int value;
}  global_vars[NUM_GLOBAL_VARS];

struct var_type local_var_stack[NUM_LOCAL_VARS];

struct func_type {
  char func_name[ID_LEN];
  int ret_type; 
  char *loc;  /* location of entry point in file */
} func_table[NUM_FUNC];

int call_stack[NUM_FUNC];

struct commands { /* keyword lookup table */
  char command[20];
  char tok;
} table[] = { /* Commands must be entered lowercase */
  "if", IF, /* in this table. */
  "else", ELSE,
  "for", FOR,
  "do", DO,
  "while", WHILE,
  "char", CHAR,
  "int", INT,
  "return", RETURN,
  "end", END,
  "", END  /* mark end of table */
};

char token[80];
char token_type, tok;

int functos;  /* index to top of function call stack */
int func_index; /* index into function table */
int gvar_index; /* index into global variable table */
int lvartos; /* index into local variable stack */

int ret_value; /* function return value */

void print(void), prescan(void);
void decl_global(void), call(void), putback(void);
void decl_local(void), local_push(struct var_type i);
void eval_exp(int *value), sntx_err(int error);
void exec_if(void), find_eob(void), exec_for(void);
void get_params(void), get_args(void);
void exec_while(void), func_push(int i), exec_do(void);
void assign_var(char *var_name, int value);
int load_program(char *p, char *fname), find_var(char *s);
void interp_block(void), func_ret(void);
int func_pop(void), is_var(char *s), get_token(void);
char *find_func(char *name);

int main(int argc, char *argv[])
{
  if(argc != 2) {
    printf("Usage: littlec <filename>\n");
    exit(1);
  }

  /* allocate memory for the program */
  if((p_buf = (char *) malloc(PROG_SIZE))==NULL) {
    printf("Allocation Failure");
    exit(1);
  }

  /* load the program to execute */
  if(!load_program(p_buf, argv[1])) exit(1);
  if(setjmp(e_buf)) exit(1); /* initialize long jump buffer */

  gvar_index = 0;  /* initialize global variable index */

  /* set program pointer to start of program buffer */
  prog = p_buf;
  prescan(); /* find the location of all functions
                and global variables in the program */

  lvartos = 0;     /* initialize local variable stack index */
  functos = 0;     /* initialize the CALL stack index */

  /* setup call to main() */
  prog = find_func("main"); /* find program starting point */

  if(!prog) { /* incorrect or missing main() function in program */
    printf("main() not found.\n");
    exit(1);
  }

  prog--; /* back up to opening ( */
  strcpy(token, "main");
  call(); /* call main() to start interpreting */

  return 0;
}

/* Interpret a single statement or block of code. When
   interp_block() returns from its initial call, the final
   brace (or a return) in main() has been encountered.
*/
void interp_block(void)
{
  int value;
  char block = 0;

  do {
    token_type = get_token();

    /* If interpreting single statement, return on
       first semicolon.
    */

    /* see what kind of token is up */
    if(token_type == IDENTIFIER) {
      /* Not a keyword, so process expression. */
      putback();  /* restore token to input stream for
                     further processing by eval_exp() */
      eval_exp(&value);  /* process the expression */
      if(*token!=';') sntx_err(SEMI_EXPECTED);
    }
    else if(token_type==BLOCK) { /* if block delimiter */
      if(*token == '{') /* is a block */
        block = 1; /* interpreting block, not statement */
      else return; /* is a }, so return */
    }
    else /* is keyword */
      switch(tok) {
        case CHAR:
        case INT:     /* declare local variables */
          putback();
          decl_local();
          break;
        case RETURN:  /* return from function call */
          func_ret();
          return;
        case IF:      /* process an if statement */
          exec_if();
          break;
        case ELSE:    /* process an else statement */
          find_eob(); /* find end of else block
                         and continue execution */
          break;
        case WHILE:   /* process a while loop */
          exec_while();
          break;
        case DO:      /* process a do-while loop */
          exec_do();
          break;
        case FOR:     /* process a for loop */
          exec_for();
          break;
        case END:
          exit(0);
      }
  } while (tok != FINISHED && block);
}

/* Load a program. */
int load_program(char *p, char *fname)
{
  FILE *fp;
  int i=0;

  if((fp=fopen(fname, "rb"))==NULL) return 0;

  i = 0;
  do {
    *p = getc(fp);
    p++; i++;
  } while(!feof(fp) && i<PROG_SIZE);

  if(*(p-2) == 0x1a) *(p-2) = '\0'; /* null terminate the program */
  else *(p-1) = '\0';
  fclose(fp);
  return 1;
}

/* Find the location of all functions in the program
   and store global variables. */
void prescan(void)
{
  char *p, *tp;
  char temp[32];
  int datatype; 
  int brace = 0;  /* When 0, this var tells us that
                     current source position is outside
                     of any function. */

  p = prog;
  func_index = 0;
  do {
    while(brace) {  /* bypass code inside functions */
      get_token();
      if(*token == '{') brace++;
      if(*token == '}') brace--;
    }

    tp = prog; /* save current position */
    get_token();
    /* global var type or function return type */
    if(tok==CHAR || tok==INT) { 
      datatype = tok; /* save data type */
      get_token();
      if(token_type == IDENTIFIER) {
        strcpy(temp, token);
        get_token();
        if(*token != '(') { /* must be global var */
          prog = tp; /* return to start of declaration */
          decl_global();
        }
        else if(*token == '(') {  /* must be a function */
          func_table[func_index].loc = prog;
          func_table[func_index].ret_type = datatype;
          strcpy(func_table[func_index].func_name, temp);
          func_index++;
          while(*prog != ')') prog++;
          prog++;
          /* now prog points to opening curly 
             brace of function */
        }
        else putback();
      }
    }
    else if(*token == '{') brace++;
  } while(tok != FINISHED);
  prog = p;
}

/* Return the entry point of the specified function.
   Return NULL if not found.
*/
char *find_func(char *name)
{
  register int i;

  for(i=0; i < func_index; i++)
    if(!strcmp(name, func_table[i].func_name))
      return func_table[i].loc;

  return NULL;
 }

/* Declare a global variable. */
void decl_global(void)
{
  int vartype;

  get_token();  /* get type */

  vartype = tok; /* save var type */

  do { /* process comma-separated list */
    global_vars[gvar_index].v_type = vartype;
    global_vars[gvar_index].value = 0;  /* init to 0 */
    get_token();  /* get name */
    strcpy(global_vars[gvar_index].var_name, token);
    get_token();
    gvar_index++;
  } while(*token == ',');
  if(*token != ';') sntx_err(SEMI_EXPECTED);
}

/* Declare a local variable. */
void decl_local(void)
{
  struct var_type i;

  get_token();  /* get type */

  i.v_type = tok;
  i.value = 0;  /* init to 0 */

  do { /* process comma-separated list */
    get_token(); /* get var name */
    strcpy(i.var_name, token);
    local_push(i);
    get_token();
  } while(*token == ',');
  if(*token != ';') sntx_err(SEMI_EXPECTED);
}

/* Call a function. */
void call(void)
{
  char *loc, *temp;
  int lvartemp;

  loc = find_func(token); /* find entry point of function */
  if(loc == NULL)
    sntx_err(FUNC_UNDEF); /* function not defined */
  else {
    lvartemp = lvartos;  /* save local var stack index */
    get_args();  /* get function arguments */
    temp = prog; /* save return location */
    func_push(lvartemp);  /* save local var stack index */
    prog = loc;  /* reset prog to start of function */
    get_params(); /* load the function's parameters with
                     the values of the arguments */
    interp_block(); /* interpret the function */
    prog = temp; /* reset the program pointer */
    lvartos = func_pop(); /* reset the local var stack */
  }
}

/* Push the arguments to a function onto the local
   variable stack. */
void get_args(void)
{
  int value, count, temp[NUM_PARAMS];
  struct var_type i;

  count = 0;
  get_token();
  if(*token != '(') sntx_err(PAREN_EXPECTED);

  /* process a comma-separated list of values */
  do {
    eval_exp(&value);
    temp[count] = value;  /* save temporarily */
    get_token();
    count++;
  }while(*token == ',');
  count--;
  /* now, push on local_var_stack in reverse order */
  for(; count>=0; count--) {
    i.value = temp[count];
    i.v_type = ARG;
    local_push(i);
  }
}

/* Get function parameters. */
void get_params(void)
{
  struct var_type *p;
  int i;

  i = lvartos-1;
  do { /* process comma-separated list of parameters */
    get_token();
    p = &local_var_stack[i];
    if(*token != ')' ) {
      if(tok != INT && tok != CHAR)
        sntx_err(TYPE_EXPECTED);

      p->v_type = token_type;
      get_token();

      /* link parameter name with argument already on
         local var stack */
      strcpy(p->var_name, token);
      get_token();
      i--;
    }
    else break;
  } while(*token == ',');
  if(*token != ')') sntx_err(PAREN_EXPECTED);
}

/* Return from a function. */
void func_ret(void)
{
  int value;

  value = 0;
  /* get return value, if any */
  eval_exp(&value);

  ret_value = value;
}

/* Push a local variable. */
void local_push(struct var_type i)
{
  if(lvartos > NUM_LOCAL_VARS)
    sntx_err(TOO_MANY_LVARS);

  local_var_stack[lvartos] = i;
  lvartos++;
}

/* Pop index into local variable stack. */
int func_pop(void)
{
  functos--;
  if(functos < 0) sntx_err(RET_NOCALL);
  return call_stack[functos];
}

/* Push index of local variable stack. */
void func_push(int i)
{
  if(functos>NUM_FUNC)
   sntx_err(NEST_FUNC);
  call_stack[functos] = i;
  functos++;
}

/* Assign a value to a variable. */
void assign_var(char *var_name, int value)
{
  register int i;

  /* first, see if it's a local variable */
  for(i=lvartos-1; i >= call_stack[functos-1]; i--)  {
    if(!strcmp(local_var_stack[i].var_name, var_name)) {
      local_var_stack[i].value = value;
      return;
    }
  }
  if(i < call_stack[functos-1])
  /* if not local, try global var table */
    for(i=0; i < NUM_GLOBAL_VARS; i++)
      if(!strcmp(global_vars[i].var_name, var_name)) {
        global_vars[i].value = value;
        return;
      }
  sntx_err(NOT_VAR); /* variable not found */
}

/* Find the value of a variable. */
int find_var(char *s)
{
  register int i;

  /* first, see if it's a local variable */
  for(i=lvartos-1; i >= call_stack[functos-1]; i--)
    if(!strcmp(local_var_stack[i].var_name, token))
      return local_var_stack[i].value;

  /* otherwise, try global vars */
  for(i=0; i < NUM_GLOBAL_VARS; i++)
    if(!strcmp(global_vars[i].var_name, s))
      return global_vars[i].value;

  sntx_err(NOT_VAR); /* variable not found */
  return -1; 
}

/* Determine if an identifier is a variable. Return
   1 if variable is found; 0 otherwise.
*/
int is_var(char *s)
{
  register int i;

  /* first, see if it's a local variable */
  for(i=lvartos-1; i >= call_stack[functos-1]; i--)
    if(!strcmp(local_var_stack[i].var_name, token))
      return 1;

  /* otherwise, try global vars */
  for(i=0; i < NUM_GLOBAL_VARS; i++)
    if(!strcmp(global_vars[i].var_name, s))
      return 1;

  return 0;
}

/* Execute an if statement. */
void exec_if(void)
{
  int cond;

  eval_exp(&cond); /* get if expression */

  if(cond) { /* is true so process target of IF */
    interp_block();
  }
  else { /* otherwise skip around IF block and
            process the ELSE, if present */
    find_eob(); /* find start of next line */
    get_token();

    if(tok != ELSE) {
      putback();  /* restore token if
                     no ELSE is present */
      return;
    }
    interp_block();
  }
}

/* Execute a while loop. */
void exec_while(void)
{
  int cond;
  char *temp;

  putback();
  temp = prog;  /* save location of top of while loop */
  get_token();
  eval_exp(&cond);  /* check the conditional expression */
  if(cond) interp_block();  /* if true, interpret */
  else {  /* otherwise, skip around loop */
    find_eob();
    return;
  }
  prog = temp;  /* loop back to top */
}

/* Execute a do loop. */
void exec_do(void)
{
  int cond;
  char *temp;

  putback();
  temp = prog;  /* save location of top of do loop */

  get_token(); /* get start of loop */
  interp_block(); /* interpret loop */
  get_token();
  if(tok != WHILE) sntx_err(WHILE_EXPECTED);
  eval_exp(&cond); /* check the loop condition */
  if(cond) prog = temp; /* if true loop; otherwise,
                           continue on */
}

/* Find the end of a block. */
void find_eob(void)
{
  int brace;

  get_token();
  brace = 1;
  do {
    get_token();
    if(*token == '{') brace++;
    else if(*token == '}') brace--;
  } while(brace);
}

/* Execute a for loop. */
void exec_for(void)
{
  int cond;
  char *temp, *temp2;
  int brace ;

  get_token();
  eval_exp(&cond);  /* initialization expression */
  if(*token != ';') sntx_err(SEMI_EXPECTED);
  prog++; /* get past the ; */
  temp = prog;
  for(;;) {
    eval_exp(&cond);  /* check the condition */
    if(*token != ';') sntx_err(SEMI_EXPECTED);
    prog++; /* get past the ; */
    temp2 = prog;

    /* find the start of the for block */
    brace = 1;
    while(brace) {
      get_token();
      if(*token == '(') brace++;
      if(*token == ')') brace--;
    }

    if(cond) interp_block();  /* if true, interpret */
    else {  /* otherwise, skip around loop */
      find_eob();
      return;
    }
    prog = temp2;
    eval_exp(&cond); /* do the increment */
    prog = temp;  /* loop back to top */
  }
}

listing 10
/* Declare a local variable. */
void decl_local(void)
{
  struct var_type i;

  get_token();  /* get type */

  i.v_type = tok;
  i.value = 0;  /* init to 0 */

  do { /* process comma-separated list */
    get_token(); /* get var name */
    strcpy(i.var_name, token);
    local_push(i);
    get_token();
  } while(*token == ',');
  if(*token != ';') sntx_err(SEMI_EXPECTED);
}

/* Push a local variable. */
void local_push(struct var_type i)
{
  if(lvartos > NUM_LOCAL_VARS)
    sntx_err(TOO_MANY_LVARS);

  local_var_stack[lvartos] = i;
  lvartos++;
}

listing 11
/* Call a function. */
void call(void)
{
  char *loc, *temp;
  int lvartemp;

  loc = find_func(token); /* find entry point of function */
  if(loc == NULL)
    sntx_err(FUNC_UNDEF); /* function not defined */
  else {
    lvartemp = lvartos;  /* save local var stack index */
    get_args();  /* get function arguments */
    temp = prog; /* save return location */
    func_push(lvartemp);  /* save local var stack index */
    prog = loc;  /* reset prog to start of function */
    get_params(); /* load the function's parameters with
                     the values of the arguments */
    interp_block(); /* interpret the function */
    prog = temp; /* reset the program pointer */
    lvartos = func_pop(); /* reset the local var stack */
  }
}

/* Push the arguments to a function onto the local
   variable stack. */
void get_args(void)
{
  int value, count, temp[NUM_PARAMS];
  struct var_type i;

  count = 0;
  get_token();
  if(*token != '(') sntx_err(PAREN_EXPECTED);

  /* process a comma-separated list of values */
  do {
    eval_exp(&value);
    temp[count] = value;  /* save temporarily */
    get_token();
    count++;
  } while(*token == ',');
  count--;
  /* now, push on local_var_stack in reverse order */
  for(; count>=0; count--) {
    i.value = temp[count];
    i.v_type = ARG;
    local_push(i);
  }
}

/* Get function parameters. */
void get_params(void)
{
  struct var_type *p;
  int i;

  i = lvartos-1;
  do { /* process comma-separated list of parameters */
    get_token();
    p = &local_var_stack[i];
    if(*token != ')' ) {
      if(tok != INT && tok != CHAR)
        sntx_err(TYPE_EXPECTED);

      p->v_type = token_type;
      get_token();

      /* link parameter name with argument already on
         local var stack */
      strcpy(p->var_name, token);
      get_token();
      i--;
    }
    else break;
  } while(*token == ',');
  if(*token != ')') sntx_err(PAREN_EXPECTED);
}

listing 12
/* Return from a function. */
void func_ret(void)
{
  int value;

  value = 0;
  /* get return value, if any */
  eval_exp(&value);

  ret_value = value;
}

listing 13
/* Assign a value to a variable. */
void assign_var(char *var_name, int value)
{
  register int i;

  /* first, see if it's a local variable */
  for(i=lvartos-1; i >= call_stack[functos-1]; i--)  {
    if(!strcmp(local_var_stack[i].var_name, var_name)) {
      local_var_stack[i].value = value;
      return;
    }
  }
  if(i < call_stack[functos-1])
  /* if not local, try global var table */
    for(i=0; i < NUM_GLOBAL_VARS; i++)
      if(!strcmp(global_vars[i].var_name, var_name)) {
        global_vars[i].value = value;
        return;
      }
  sntx_err(NOT_VAR); /* variable not found */
}

listing 14
/* Execute an if statement. */
void exec_if(void)
{
  int cond;

  eval_exp(&cond); /* get if expression */

  if(cond) { /* is true so process target of IF */
    interp_block();
  }
  else { /* otherwise skip around IF block and
            process the ELSE, if present */
    find_eob(); /* find start of next line */
    get_token();

    if(tok != ELSE) {
      putback();  /* restore token if
                     no ELSE is present */
      return;
    }
    interp_block();
  }
}

listing 15
/* Execute a while loop. */
void exec_while(void)
{
  int cond;
  char *temp;

  putback();
  temp = prog;  /* save location of top of while loop */
  get_token();
  eval_exp(&cond);  /* check the conditional expression */
  if(cond) interp_block();  /* if true, interpret */
  else {  /* otherwise, skip around loop */
    find_eob();
    return;
  }
  prog = temp;  /* loop back to top */
}

listing 16
/* Execute a do loop. */
void exec_do(void)
{
  int cond;
  char *temp;

  putback();
  temp = prog;  /* save location of top of do loop */

  get_token(); /* get start of loop */
  interp_block(); /* interpret loop */
  get_token();
  if(tok != WHILE) sntx_err(WHILE_EXPECTED);
  eval_exp(&cond); /* check the loop condition */
  if(cond) prog = temp; /* if true loop; otherwise,
                           continue on */
}

listing 17
/* Execute a for loop. */
void exec_for(void)
{
  int cond;
  char *temp, *temp2;
  int brace ;

  get_token();
  eval_exp(&cond);  /* initialization expression */
  if(*token != ';') sntx_err(SEMI_EXPECTED);
  prog++; /* get past the ; */
  temp = prog;
  for(;;) {
    eval_exp(&cond);  /* check the condition */
    if(*token != ';') sntx_err(SEMI_EXPECTED);
    prog++; /* get past the ; */
    temp2 = prog;

    /* find the start of the for block */
    brace = 1;
    while(brace) {
      get_token();
      if(*token == '(') brace++;
      if(*token == ')') brace--;
    }

    if(cond) interp_block();  /* if true, interpret */
    else {  /* otherwise, skip around loop */
      find_eob();
      return;
    }
    prog = temp2;
    eval_exp(&cond); /* do the increment */
    prog = temp;  /* loop back to top */
  }
}

listing 18
int getche(void);    /* read a character from keyboard and 
                          return its value */
int putch(char ch);  /* write a character to the screen */
int puts(char *s);   /* write a string to the screen */
int getnum(void);    /* read an integer from the keyboard and
                          return its value */
int print(char *s);  /* write a string to the screen */
or
int print(int i);    /* write an integer to the screen */

listing 19
/****** Internal Library Functions *******/

/* Add more of your own, here. */

#include <conio.h>  /* if your compiler does not
                       support this  header file,
                       remove it */
#include <stdio.h>
#include <stdlib.h>

extern char *prog; /* points to current location in program */
extern char token[80]; /* holds string representation of token */
extern char token_type; /* contains type of token */
extern char tok; /* holds the internal representation of token */

enum tok_types {DELIMITER, IDENTIFIER, NUMBER, KEYWORD,
                TEMP, STRING, BLOCK};

/* These are the constants used to call sntx_err() when
   a syntax error occurs. Add more if you like.
   NOTE: SYNTAX is a generic error message used when
   nothing else seems appropriate.
*/
enum error_msg
     {SYNTAX, UNBAL_PARENS, NO_EXP, EQUALS_EXPECTED,
      NOT_VAR, PARAM_ERR, SEMI_EXPECTED,
      UNBAL_BRACES, FUNC_UNDEF, TYPE_EXPECTED,
      NEST_FUNC, RET_NOCALL, PAREN_EXPECTED,
      WHILE_EXPECTED, QUOTE_EXPECTED, NOT_STRING,
      TOO_MANY_LVARS, DIV_BY_ZERO};

int get_token(void);
void sntx_err(int error), eval_exp(int *result);
void putback(void);

/* Get a character from console. (Use getchar() if
   your compiler does not support _getche().) */
int call_getche()
{
  char ch;
  ch = _getche();
  while(*prog!=')') prog++;
  prog++;   /* advance to end of line */
  return ch;
}

/* Put a character to the display. */
int call_putch()
{
  int value;

  eval_exp(&value);
  printf("%c", value);
  return value;
}

/* Call puts(). */
int call_puts(void)
{
  get_token();
  if(*token!='(') sntx_err(PAREN_EXPECTED);
  get_token();
  if(token_type!=STRING) sntx_err(QUOTE_EXPECTED);
  puts(token);
  get_token();
  if(*token!=')') sntx_err(PAREN_EXPECTED);

  get_token();
  if(*token!=';') sntx_err(SEMI_EXPECTED);
  putback();
  return 0;
}

/* A built-in console output function. */
int print(void)
{
  int i;

  get_token();
  if(*token!='(')  sntx_err(PAREN_EXPECTED);

  get_token();
  if(token_type==STRING) { /* output a string */
    printf("%s ", token);
  }
  else {  /* output a number */
   putback();
   eval_exp(&i);
   printf("%d ", i);
  }

  get_token();

  if(*token!=')') sntx_err(PAREN_EXPECTED);

  get_token();
  if(*token!=';') sntx_err(SEMI_EXPECTED);
  putback();
  return 0;
}

/* Read an integer from the keyboard. */
int getnum(void)
{
  char s[80];

  gets(s);
  while(*prog != ')') prog++;
  prog++;  /* advance to end of line */
  return atoi(s);
}


listing 20
/* Little C Demonstration Program #1.

   This program demonstrates all features
   of C that are recognized by Little C.
*/

int i, j;   /* global vars */
char ch;

int main()
{
  int i, j;  /* local vars */

  puts("Little C Demo Program.");

  print_alpha();

  do {
    puts("enter a number (0 to quit): ");
    i = getnum();
    if(i < 0 ) {
      puts("numbers must be positive, try again");
    }
    else {
      for(j = 0; j < i; j=j+1) {
        print(j);
        print("summed is");
        print(sum(j));
        puts("");
      }
    }
  } while(i!=0);

  return 0;
}

/* Sum the values between 0 and num. */
int sum(int num)
{
  int running_sum;

  running_sum = 0;

  while(num) {
    running_sum = running_sum + num;
    num = num - 1;
  }
  return running_sum;
}

/* Print the alphabet. */
int print_alpha()
{
  for(ch = 'A'; ch<='Z'; ch = ch + 1) {
    putch(ch);
  }
  puts("");

  return 0;
}

listing 21
/* Nested loop example. */
int main()
{
  int i, j, k;

  for(i = 0; i < 5; i = i + 1) {
    for(j = 0; j < 3; j = j + 1) {
      for(k = 3; k ; k = k - 1) {
        print(i);
        print(j);
        print(k);
        puts("");
      }
    }
  }
  puts("done");

  return 0;
}

listing 22
/* Assigments as operations. */
int main()
{
  int a, b;

  a = b = 10;

  print(a); print(b);

  while(a=a-1) {
    print(a);
    do {
       print(b);
    } while((b=b-1) > -10);
  }

  return 0;
}

listing 23
/* This program demonstrates recursive functions. */

/* return the factorial of i */
int factr(int i)
{
  if(i<2) {
    return 1;
  }
  else {
     return i * factr(i-1);
  }
}

int main()
{
  print("Factorial of 4 is: ");
  print(factr(4));

  return 0;
}

listing 24
/* A more rigorous example of function arguments. */

int f1(int a, int b)
{
  int count;

  print("in f1");

  count = a;
  do {
    print(count);
  } while(count=count-1);

  print(a); print(b);
  print(a*b);
  return a*b;
}

int f2(int a, int x, int y)
{
  print(a); print(x);
  print(x / a);
  print(y*x);

  return 0;
}

int main()
{
  f2(10, f1(10, 20), 99);

  return 0;
}

listing 25
/* The loop statements. */
int main()
{
  int a;
  char ch;

  /* the while */
  puts("Enter a number: ");
  a = getnum();
  while(a) {
    print(a);
    print(a*a);
    puts("");
    a = a - 1;
  }

  /* the do-while */
  puts("enter characters, 'q' to quit");
  do {
     ch = getche();
  } while(ch !='q');

  /* the for */
  for(a=0; a<10; a = a + 1) {
     print(a);
  }

  return 0;
}

