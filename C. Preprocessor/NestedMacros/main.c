// fn_tbl.c: Display values of a function in tabular form.
// This program uses nested macros.
// -------------------------------------------------------------

#include <stdio.h>
#include <math.h>      // Prototypes of the cos() and exp() functions.

#define PI          3.141593
#define STEP        (PI/8)
#define AMPLITUDE   1.0
#define ATTENUATION 0.1            // Attenuation in wave propagation.
#define DF(x)       exp(-ATTENUATION*(x))
#define FUNC(x)     (DF(x) * AMPLITUDE * cos(x))   // Attenuated
// oscillation.
// For the function display:
#define STR(s)  #s
#define XSTR(s) STR(s)       // Expand the macros in s, then stringify.

int main()
{
	double x = 0.0;

	printf("\nFUNC(x) = %s\n", XSTR(FUNC(x)));    // Print the function.

	printf("\n %10s %25s\n", "x", STR(y = FUNC(x)));     // Table header.
	printf("-----------------------------------------\n");
	for (; x < 2 * PI + STEP / 2; x += STEP)
		printf("%15f %20f\n", x, FUNC(x));

	return 0;
}
