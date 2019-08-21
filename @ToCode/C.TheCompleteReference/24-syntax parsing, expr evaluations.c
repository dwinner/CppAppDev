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
