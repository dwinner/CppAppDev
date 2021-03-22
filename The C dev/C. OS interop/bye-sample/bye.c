/**
 * atexit() example
 */

#include <stdio.h>
#include <stdlib.h>

void signOff(void);
void tooBad(void);

int main(void)
{
	int n;

	atexit(signOff); /* register the sign_off() function */
	puts("Enter an integer:");
	if (scanf("%d", &n) != 1)
	{
		puts("That's no integer!");
		atexit(tooBad); /* register the too_bad()  function */
		exit(EXIT_FAILURE);
	}
	printf("%d is %s.\n", n, (n % 2 == 0) ? "even" : "odd");

	return 0;
}

void signOff(void)
{
	puts("Thus terminates another magnificent program from");
	puts("SeeSaw Software!");
}

void tooBad(void)
{
	puts("SeeSaw Software extends its heartfelt condolences");
	puts("to you upon the failure of your program.");
}
