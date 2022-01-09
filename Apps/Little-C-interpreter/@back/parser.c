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