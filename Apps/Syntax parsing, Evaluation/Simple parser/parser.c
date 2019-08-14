#include "parser.h"

/**
 * \brief Точка входа анализатора
 * \param answer 
 */
void start_evaluation(double* answer)
{
	get_token();
	if (!*token)
	{
		seterror(2);
		return;
	}

	add_or_subtract(answer);

	if (*token)
	{
		seterror(0);	/* Последней лексемой должен быть нуль */
	}
}

/**
 * \brief Сложение или вычитание 2-х слагаемых
 * \param answer 
 */
void add_or_subtract(double* answer)
{
	register char op;
	double temp;

	multiply_or_divide(answer);
	while ((op=*token)=='+'||op=='-')
	{
		get_token();
		multiply_or_divide(&temp);
		switch (op)
		{
		case '-':
			*answer = *answer - temp;
			break;

		case '+':
			*answer = *answer + temp;
			break;

		default: 
			break;
		}
	}
}

/**
 * \brief Умножение или деление 2-х множителей
 * \param answer 
 */
void multiply_or_divide(double* answer)
{
	register char op;
	double temp;

	power(answer);
	while ((op=*token)=='*'||op=='/'||op=='%')
	{
		get_token();
		power(&temp);
		switch (op)
		{
		case '*':
			*answer = *answer*temp;
			break;

		case '/':
			if (temp==0.0)
			{
				seterror(3);	/* Деление на 0 */
				*answer = 0.0;
			}
			else
			{
				*answer = *answer / temp;
			}

			break;

		case '%':
			*answer = (int)*answer % (int)temp;
			break;

		default:
			break;
		}
	}
}

/**
 * \brief Возведение в степень
 * \param answer 
 */
void power(double* answer)
{
	double temp, ex;
	register int t;

	unary_plus_minus(answer);

	if (*token=='^')
	{
		get_token();
		power(&temp);
		ex = *answer;
		if (temp==0.0)
		{
			*answer = 1.0;
			return;
		}

		for (t = temp - 1; t > 0; --t)
		{
			*answer = (*answer)*(double)ex;
		}
	}
}

/**
 * \brief Вычисление унарных операторов + и -
 * \param answer 
 */
void unary_plus_minus(double* answer)
{
	register char op;

	op = 0;
	if ((token_type==DELIMETER) && *token=='+'|| *token=='-')
	{
		op = *token;
		get_token();
	}

	eval_brackets(answer);

	if (op=='-')
	{
		*answer = -(*answer);
	}
}

/**
 * \brief Вычисление выражения в скобках
 * \param answer 
 */
void eval_brackets(double* answer)
{
	if ((*token=='('))
	{
		get_token();
		add_or_subtract(answer);
		if (*token!=')')
		{
			seterror(1);
		}

		get_token();
	}
	else
	{
		atom(answer);
	}
}

/**
 * \brief Получение значения числа
 * \param answer 
 */
void atom(double* answer)
{
	if (token_type==NUMBER)
	{
		*answer = atof(token);
		get_token();
		return;
	}

	seterror(0);	/* иначе синтаксическая ошибка в выражении */
}

/**
 * \brief Возврат очередной лексемы
 */
void get_token()
{
	register char *temp;

	token_type = 0;
	temp = token;
	*temp = '\0';

	if (!*prog)
	{
		return;	/* Конец выражения */
	}

	while (isspace(*prog))
	{
		/* пропустить пробелы, символы табуляции и пустой строки */
		++prog;
	}

	if (strchr("+-*/%^=()",*prog))
	{
		token_type = DELIMETER;
		/* Перейти к следующему символу */
		*temp++ = *prog++;
	}
	else if (isalpha(*prog))
	{
		while (!is_delim(*prog))
		{
			*temp++ = *prog++;
		}

		token_type = VARIABLE;
	}
	else if (isdigit(*prog))
	{
		while (!is_delim(*prog))
		{
			*temp++ = *prog++;
		}

		token_type = NUMBER;
	}

	*temp = '\0';
}

/**
 * \brief Возврат лексемы в выходной поток 
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
 * \brief Отображение сообщения об ошибке
 * \param error Код ошибки
 */
void seterror(int error)
{
	static char *e[]=
	{
		"Syntax error",
		"Unbalanced brackets",
		"No expression",
		"Dividing by zero"
	};

	printf("%s\n", e[error]);
}

/**
 * \brief Возвращает значение true, если c является разделителем
 * \param c Символ
 * \return 1, если c разделитель, 0 в противном случае
 */
int is_delim(char c)
{
	return strchr(" +-/*%^=()", c) || c == 9 || c == '\r' || c == 0
		? 1
		: 0;
}
