/**
 *	Using variable-length argument lists
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

double average(int anArgCount, ...);

int main()
{
	double w = 37.5;
	double x = 22.5;
	double y = 1.7;
	double z = 10.2;

	printf("%s%.1f\n%s%.1f\n%s%.1f\n%s%.1f\n\n",
	       "w = ", w, "x = ", x, "y = ", y, "z = ", z);
	printf("%s%.3f\n%s%.3f\n%s%.3f\n",
	       "The average of w and x is ", average(2, w, x),
	       "The average of w, x, and y is ", average(3, w, x, y),
	       "The average of w, x, y, and z is ",
	       average(4, w, x, y, z));

	return EXIT_SUCCESS;
}

/**
 * \brief Calculate average sum
 * \param anArgCount count of parameters
 * \param ... Variable length signature
 * \return Average number
 */
double average(int anArgCount, ...)
{
	double total = 0.0;

	va_list ap;
	va_start(ap, anArgCount);
	for (int j = 1; j <= anArgCount; ++j)
	{
		total += va_arg(ap, double);
	}
	va_end(ap);

	return total / anArgCount;
}
