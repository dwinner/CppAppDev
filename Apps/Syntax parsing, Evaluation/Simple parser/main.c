/**
 *	Этот модуль содержит простой синтаксический анализатор,
 *	который не распознает переменные
 */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

char *prog;

int main(int argc, char* argv[])
{
	double answer;
	char *p;

	p = (char*)malloc(100);
	if (!p)
	{
		printf("Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	/* Обработка выражений до ввода пустой строки */
	do
	{
		prog = p;
		printf("Enter expression: ");
		gets_s(prog, 100);
		if (!*prog)
		{
			break;
		}

		start_evaluation(&answer);
		printf("Result: %.2f\n", answer);
	}
	while (*p);

	return EXIT_SUCCESS;
}
