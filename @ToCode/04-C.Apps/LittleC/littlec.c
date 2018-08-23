/* Find the location of all functions in the program
   and store global variables. */
void prescan(void)
{
	char *p, *tp;
	char temp[ID_LEN + 1];
	int datatype;
	int brace = 0;  /* When 0, this var tells us that
					   current source position is outside
					   of any function. */

	p = prog;
	func_index = 0;
	do {
		while (brace) {  /* bypass code inside functions */
			get_token();
			if (*token == '{') brace++;
			if (*token == '}') brace--;
		}

		tp = prog; /* save current position */
		get_token();
		/* global var type or function return type */
		if (tok == CHAR || tok == INT) {
			datatype = tok; /* save data type */
			get_token();
			if (token_type == IDENTIFIER) {
				strcpy(temp, token);
				get_token();
				if (*token != '(') { /* must be global var */
					prog = tp; /* return to start of declaration */
					decl_global();
				}
				else if (*token == '(') {  /* must be a function */
					func_table[func_index].loc = prog;
					func_table[func_index].ret_type = datatype;
					strcpy(func_table[func_index].func_name, temp);
					func_index++;
					while (*prog != ')') prog++;
					prog++;
					/* now prog points to opening curly
					   brace of function */
				}
				else putback();
			}
		}
		else if (*token == '{') brace++;
	} while (tok != FINISHED);
	prog = p;
}

/* Return the entry point of the specified function.
   Return NULL if not found.
*/
char *find_func(char *name)
{
	register int i;

	for (i = 0; i < func_index; i++)
		if (!strcmp(name, func_table[i].func_name))
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
	} while (*token == ',');
	if (*token != ';') sntx_err(SEMI_EXPECTED);
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
	} while (*token == ',');
	if (*token != ';') sntx_err(SEMI_EXPECTED);
}

/* Call a function. */
void call(void)
{
	char *loc, *temp;
	int lvartemp;

	loc = find_func(token); /* find entry point of function */
	if (loc == NULL)
		sntx_err(FUNC_UNDEF); /* function not defined */
	else {
		lvartemp = lvartos;  /* save local var stack index */
		get_args();  /* get function arguments */
		temp = prog; /* save return location */
		func_push(lvartemp);  /* save local var stack index */
		prog = loc;  /* reset prog to start of function */
		ret_occurring = 0; /* P the return occurring variable */
		get_params(); /* load the function's parameters with the values of the arguments */
		interp_block(); /* interpret the function */
		ret_occurring = 0; /* Clear the return occurring variable */
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
	if (*token != '(') sntx_err(PAREN_EXPECTED);

	/* process a comma-separated list of values */
	do {
		eval_exp(&value);
		temp[count] = value;  /* save temporarily */
		get_token();
		count++;
	} while (*token == ',');
	count--;
	/* now, push on local_var_stack in reverse order */
	for (; count >= 0; count--) {
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

	i = lvartos - 1;
	do { /* process comma-separated list of parameters */
		get_token();
		p = &local_var_stack[i];
		if (*token != ')') {
			if (tok != INT && tok != CHAR)
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
	} while (*token == ',');
	if (*token != ')') sntx_err(PAREN_EXPECTED);
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
	if (lvartos >= NUM_LOCAL_VARS) {
		sntx_err(TOO_MANY_LVARS);
	}
	else {
		local_var_stack[lvartos] = i;
		lvartos++;
	}
}

/* Pop index into local variable stack. */
int func_pop(void)
{
	int index = 0;
	functos--;
	if (functos < 0) {
		sntx_err(RET_NOCALL);
	}
	else if (functos >= NUM_FUNC) {
		sntx_err(NEST_FUNC);
	}
	else {
		index = call_stack[functos];
	}

	return index;
}

/* Push index of local variable stack. */
void func_push(int i)
{
	if (functos >= NUM_FUNC) {
		sntx_err(NEST_FUNC);
	}
	else {
		call_stack[functos] = i;
		functos++;
	}
}

/* Assign a value to a variable. */
void assign_var(char *var_name, int value)
{
	register int i;

	/* first, see if it's a local variable */
	for (i = lvartos - 1; i >= call_stack[functos - 1]; i--) {
		if (!strcmp(local_var_stack[i].var_name, var_name)) {
			local_var_stack[i].value = value;
			return;
		}
	}
	if (i < call_stack[functos - 1])
		/* if not local, try global var table */
		for (i = 0; i < NUM_GLOBAL_VARS; i++)
			if (!strcmp(global_vars[i].var_name, var_name)) {
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
	for (i = lvartos - 1; i >= call_stack[functos - 1]; i--)
		if (!strcmp(local_var_stack[i].var_name, token))
			return local_var_stack[i].value;

	/* otherwise, try global vars */
	for (i = 0; i < NUM_GLOBAL_VARS; i++)
		if (!strcmp(global_vars[i].var_name, s))
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
	for (i = lvartos - 1; i >= call_stack[functos - 1]; i--)
		if (!strcmp(local_var_stack[i].var_name, token))
			return 1;

	/* otherwise, try global vars */
	for (i = 0; i < NUM_GLOBAL_VARS; i++)
		if (!strcmp(global_vars[i].var_name, s))
			return 1;

	return 0;
}

/* Execute an if statement. */
void exec_if(void)
{
	int cond;

	eval_exp(&cond); /* get if expression */

	if (cond) { /* is true so process target of IF */
		interp_block();
	}
	else { /* otherwise skip around IF block and
		   process the ELSE, if present */
		find_eob(); /* find start of next line */
		get_token();

		if (tok != ELSE) {
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

	break_occurring = 0; /* clear the break flag */
	putback();
	temp = prog;  /* save location of top of while loop */
	get_token();
	eval_exp(&cond);  /* check the conditional expression */
	if (cond) {
		interp_block();  /* if true, interpret */
		if (break_occurring > 0) {
			break_occurring = 0;
			return;
		}
	}
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
	break_occurring = 0; /* clear the break flag */

	get_token(); /* get start of loop */
	interp_block(); /* interpret loop */
	if (ret_occurring > 0) {
		return;
	}
	else if (break_occurring > 0) {
		break_occurring = 0;
		return;
	}
	get_token();
	if (tok != WHILE) sntx_err(WHILE_EXPECTED);
	eval_exp(&cond); /* check the loop condition */
	if (cond) prog = temp; /* if true loop; otherwise,
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
		if (*token == '{') brace++;
		else if (*token == '}') brace--;
	} while (brace);
}

/* Execute a for loop. */
void exec_for(void)
{
	int cond;
	char *temp, *temp2;
	int brace;

	break_occurring = 0; /* clear the break flag */
	get_token();
	eval_exp(&cond);  /* initialization expression */
	if (*token != ';') sntx_err(SEMI_EXPECTED);
	prog++; /* get past the ; */
	temp = prog;
	for (;;) {
		eval_exp(&cond);  /* check the condition */
		if (*token != ';') sntx_err(SEMI_EXPECTED);
		prog++; /* get past the ; */
		temp2 = prog;

		/* find the start of the for block */
		brace = 1;
		while (brace) {
			get_token();
			if (*token == '(') brace++;
			if (*token == ')') brace--;
		}

		if (cond) {
			interp_block();  /* if true, interpret */
			if (ret_occurring > 0) {
				return;
			}
			else if (break_occurring > 0) {
				break_occurring = 0;
				return;
			}
		}
		else {  /* otherwise, skip around loop */
			find_eob();
			return;
		}
		prog = temp2;
		eval_exp(&cond); /* do the increment */
		prog = temp;  /* loop back to top */
	}
}
