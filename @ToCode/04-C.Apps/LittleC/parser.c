/* Find value of number, variable, or function. */
void atom(int *value)
{
	int i;

	switch (token_type) {
	case IDENTIFIER:
		i = internal_func(token);
		if (i != -1) {  /* call "standard library" function */
			*value = (*intern_func[i].p)();
		}
		else if (find_func(token)) { /* call user-defined function */
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
		if (*token == '\'') {
			*value = *prog;
			prog++;
			if (*prog != '\'') sntx_err(QUOTE_EXPECTED);
			prog++;
			get_token();
			return;
		}
		if (*token == ')') return; /* process empty expression */
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

	static char *e[] = {
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
	while (p != prog && *p != '\0') {  /* find line number of error */
		p++;
		if (*p == '\r') {
			linecount++;
			if (p == prog) {
				break;
			}
			/* See if this is a Windows or Mac newline */
			p++;
			/* If we are a mac, backtrack */
			if (*p != '\n') {
				p--;
			}
		}
		else if (*p == '\n') {
			linecount++;
		}
		else if (*p == '\0') {
			linecount++;
		}
	}
	printf(" in line %d\n", linecount);

	temp = p--;
	for (i = 0; i < 20 && p > p_buf && *p != '\n' && *p != '\r'; i++, p--);
	for (i = 0; i < 30 && p <= temp; i++, p++) printf("%c", *p);

	longjmp(e_buf, 1); /* return to safe point */
}

/* Get a token. */
char get_token(void)
{

	register char *temp;

	token_type = 0; tok = 0;

	temp = token;
	*temp = '\0';

	/* skip over white space */
	while (iswhite(*prog) && *prog) ++prog;

	/* Handle Windows and Mac newlines */
	if (*prog == '\r') {
		++prog;
		/* Only skip \n if it exists (if it doesn't, we are running on mac) */
		if (*prog == '\n') {
			++prog;
		}
		/* skip over white space */
		while (iswhite(*prog) && *prog) ++prog;
	}

	/* Handle Unix newlines */
	if (*prog == '\n') {
		++prog;
		/* skip over white space */
		while (iswhite(*prog) && *prog) ++prog;
	}

	if (*prog == '\0') { /* end of file */
		*token = '\0';
		tok = FINISHED;
		return (token_type = DELIMITER);
	}

	if (strchr("{}", *prog)) { /* block delimiters */
		*temp = *prog;
		temp++;
		*temp = '\0';
		prog++;
		return (token_type = BLOCK);
	}

	/* look for comments */
	if (*prog == '/')
		if (*(prog + 1) == '*') { /* is a comment */
			prog += 2;
			do { /* find end of comment */
				while (*prog != '*' && *prog != '\0') prog++;
				if (*prog == '\0') {
					prog--;
					break;
				}
				prog++;
			} while (*prog != '/');
			prog++;
		}

	/* look for C++ style comments */
	if (*prog == '/')
		if (*(prog + 1) == '/') { /* is a comment */
			prog += 2;
			/* find end of line */
			while (*prog != '\r' && *prog != '\n' && *prog != '\0') prog++;
			if (*prog == '\r' && *(prog + 1) == '\n') {
				prog++;
			}
		}

	/* look for the end of file after a comment */
	if (*prog == '\0') { /* end of file */
		*token = '\0';
		tok = FINISHED;
		return (token_type = DELIMITER);
	}

	if (strchr("!<>=", *prog)) { /* is or might be
								   a relational operator */
		switch (*prog) {
		case '=': if (*(prog + 1) == '=') {
			prog++; prog++;
			*temp = EQ;
			temp++; *temp = EQ; temp++;
			*temp = '\0';
		}
				  break;
		case '!': if (*(prog + 1) == '=') {
			prog++; prog++;
			*temp = NE;
			temp++; *temp = NE; temp++;
			*temp = '\0';
		}
				  break;
		case '<': if (*(prog + 1) == '=') {
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
		case '>': if (*(prog + 1) == '=') {
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
		if (*token) return(token_type = DELIMITER);
	}

	if (strchr("+-*^/%=;(),'", *prog)) { /* delimiter */
		*temp = *prog;
		prog++; /* advance to next position */
		temp++;
		*temp = '\0';
		return (token_type = DELIMITER);
	}

	if (*prog == '"') { /* quoted string */
		prog++;
		while ((*prog != '"' && *prog != '\r' && *prog != '\n' && *prog != '\0') || (*prog == '"' && *(prog - 1) == '\\')) *temp++ = *prog++;
		if (*prog == '\r' || *prog == '\n' || *prog == '\0') sntx_err(SYNTAX);
		prog++; *temp = '\0';
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

	if (isdigit((int)*prog)) { /* number */
		while (!isdelim(*prog)) *temp++ = *prog++;
		*temp = '\0';
		return (token_type = NUMBER);
	}

	if (isalpha((int)*prog)) { /* var or command */
		while (!isdelim(*prog)) *temp++ = *prog++;
		token_type = TEMP;
	}

	*temp = '\0';

	/* see if a string is a command or a variable */
	if (token_type == TEMP) {
		tok = look_up(token); /* convert to internal rep */
		if (tok) token_type = KEYWORD; /* is a keyword */
		else token_type = IDENTIFIER;
	}
	return token_type;
}

/* Return a token to input stream. */
void putback(void)
{
	char *t;

	t = token;
	for (; *t; t++) prog--;
}

/* Look up a token's internal representation in the
   token table.
*/
char look_up(char *s)
{
	register int i;
	char *p;

	/* convert to lowercase */
	p = s;
	while (*p) { *p = (char)tolower(*p); p++; }

	/* see if token is in table */
	for (i = 0; *table[i].command; i++) {
		if (!strcmp(table[i].command, s)) return table[i].tok;
	}
	return 0; /* unknown command */
}

/* Return index of internal library function or -1 if
   not found.
*/
int internal_func(char *s)
{
	int i;

	for (i = 0; intern_func[i].f_name[0]; i++) {
		if (!strcmp(intern_func[i].f_name, s))  return i;
	}
	return -1;
}

/* Return true if c is a delimiter. */
int isdelim(char c)
{
	if (strchr(" !;,+-<>'/*%^=()", c) || c == 9 ||
		c == '\r' || c == '\n' || c == 0) return 1;
	return 0;
}

/* Return 1 if c is space or tab. */
int iswhite(char c)
{
	if (c == ' ' || c == '\t') return 1;
	else return 0;
}

/* An in-place modification find and replace of the string.
   Assumes the buffer pointed to by line is large enough to hold the resulting string.*/
static void str_replace(char *line, const char *search, const char *replace)
{
	char *sp;
	while ((sp = strstr(line, search)) != NULL) {
		int search_len = (int)strlen(search);
		int replace_len = (int)strlen(replace);
		int tail_len = (int)strlen(sp + search_len);

		memmove(sp + replace_len, sp + search_len, tail_len + 1);
		memcpy(sp, replace, replace_len);
	}
}