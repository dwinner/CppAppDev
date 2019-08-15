listing 4
/* Return the value of a variable. */
double find_var(char *s)
{
  if(!isalpha(*s)){
    serror(1);
    return 0;
  }
  return vars[toupper(*token)-'A'];
}

listing 5
/* Get the value of a number or a variable. */
void atom(double *answer)
{
  switch(tok_type) {
    case VARIABLE:
      *answer = find_var(token);
      get_token();
      return;
    case NUMBER:
      *answer = atof(token);
      get_token();
      return;
    default:
      serror(0);
  }
}

listing 6
/* Process an assignment. */
void eval_exp1(double *result)
{
  int slot, ttok_type;
  char temp_token[80];

  if(tok_type == VARIABLE) {
    /* save old token */
    strcpy(temp_token, token);
    ttok_type = tok_type;

    /* compute the index of the variable */
    slot = toupper(*token) - 'A';

    get_token();
    if(*token != '=') {
      putback(); /* return current token */
      /* restore old token - not assignment */
      strcpy(token, temp_token);
      tok_type = ttok_type;
    }
    else {
      get_token(); /* get next part of exp */
      eval_exp2(result);
      vars[slot] = *result;
      return;
    }
  }

  eval_exp2(result);
}

listing 7
/* Return a token to the input stream. */
void putback(void)
{
  char *t;

  t = token;
  for(; *t; t++) prog--;
}

listing 8
/* This module contains the recursive descent
   parser that recognizes variables.
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3

extern char *prog; /* points to the expression to be analyzed */
char token[80];
char tok_type;

double vars[26] = { /* 26 user variables,  A-Z */
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

void eval_exp(double *answer), eval_exp2(double *answer);
void eval_exp1(double *result);
void eval_exp3(double *answer), eval_exp4(double *answer);
void eval_exp5(double *answer), eval_exp6(double *answer);
void atom(double *answer);
void get_token(void), putback(void);
void serror(int error);
double find_var(char *s);
int isdelim(char c);

/* Parser entry point. */
void eval_exp(double *answer)
{
  get_token();
  if(!*token) {
    serror(2);
    return;
  }
  eval_exp1(answer);
  if(*token) serror(0); /* last token must be null */
}

/* Process an assignment. */
void eval_exp1(double *answer)
{
  int slot;
  char ttok_type;
  char temp_token[80];

  if(tok_type == VARIABLE) {
    /* save old token */
    strcpy(temp_token, token);
    ttok_type = tok_type;
    /* compute the index of the variable */
    slot = toupper(*token) - 'A';

    get_token();
    if(*token != '=') {
      putback(); /* return current token */
      /* restore old token - not assignment */
      strcpy(token, temp_token);
      tok_type = ttok_type;
    }
    else {
      get_token(); /* get next part of exp */
      eval_exp2(answer);
      vars[slot] = *answer;
      return;
    }
  }
  eval_exp2(answer);
}

/* Add or subtract two terms. */
void eval_exp2(double *answer)
{
  register char op;
  double temp;

  eval_exp3(answer);
  while((op = *token) == '+' || op == '-') {
    get_token();
    eval_exp3(&temp);
    switch(op) {
      case '-':
        *answer = *answer - temp;
        break;
      case '+':
        *answer = *answer + temp;
        break;
    }
  }
}

/* Multiply or divide two factors. */
void eval_exp3(double *answer)
{
  register char op;
  double temp;

  eval_exp4(answer);
  while((op = *token) == '*' || op == '/' || op == '%') {
    get_token();
    eval_exp4(&temp);
    switch(op) {
      case '*':
        *answer = *answer * temp;
        break;
      case '/':
        if(temp == 0.0) {
          serror(3); /* division by zero */
          *answer = 0.0;
        } else *answer = *answer / temp;
        break;
      case '%':
        *answer = (int) *answer % (int) temp;
        break;
    }
  }
}

/* Process an exponent */
void eval_exp4(double *answer)
{
  double temp, ex;
  register int t;

  eval_exp5(answer);
  if(*token == '^') {
    get_token();
    eval_exp4(&temp);
    ex = *answer;
    if(temp==0.0) {
      *answer = 1.0;
      return;
    }
    for(t=temp-1; t>0; --t) *answer = (*answer) * (double)ex;
  }
}

/* Evaluate a unary + or -. */
void eval_exp5(double *answer)
{
  register char  op;

  op = 0;
  if((tok_type == DELIMITER) && *token=='+' || *token == '-') {
    op = *token;
    get_token();
  }
  eval_exp6(answer);
  if(op == '-') *answer = -(*answer);
}

/* Process a parenthesized expression. */
void eval_exp6(double *answer)
{
  if((*token == '(')) {
    get_token();
    eval_exp2(answer);
    if(*token != ')')
      serror(1);
    get_token();
  }
  else atom(answer);
}

/* Get the value of a number or a variable. */
void atom(double *answer)
{
  switch(tok_type) {
    case VARIABLE:
      *answer = find_var(token);
      get_token();
      return;
    case NUMBER:
      *answer = atof(token);
      get_token();
      return;
    default:
      serror(0);
  }
}

/* Return a token to the input stream. */
void putback(void)
{
  char *t;

  t = token;
  for(; *t; t++) prog--;
}

/* Display a syntax error. */
void serror(int error)
{
  static char *e[]= {
      "Syntax Error",
      "Unbalanced Parentheses",
      "No Expression Present",
      "Division by Zero"
  };
  printf("%s\n", e[error]);
}

/* Return the next token. */
void get_token(void)
{
  register char *temp;

  tok_type = 0;
  temp = token;
  *temp = '\0';

  if(!*prog) return; /* at end of expression */

  while(isspace(*prog)) ++prog; /* skip over white space */

  if(strchr("+-*/%^=()", *prog)){
    tok_type = DELIMITER;
    /* advance to next char */
    *temp++ = *prog++;
  }
  else if(isalpha(*prog)) {
    while(!isdelim(*prog)) *temp++ = *prog++;
    tok_type = VARIABLE;
  }
  else if(isdigit(*prog)) {
    while(!isdelim(*prog)) *temp++ = *prog++;
    tok_type = NUMBER;
  }

  *temp = '\0';
}

/* Return true if c is a delimiter. */
int isdelim(char c)
{
  if(strchr(" +-/*%^=()", c) || c==9 || c=='\r' || c==0)
    return 1;
  return 0;
}

/* Return the value of a variable. */
double find_var(char *s)
{
  if(!isalpha(*s)){
    serror(1);
    return 0.0;
  }
  return vars[toupper(*token)-'A'];
}

