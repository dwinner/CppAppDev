// Simple use of function pointers
// functionPointers.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Add(double x, double y)
{ return x + y; }

double Sub(double x, double y)
{ return x - y; }

double Mul(double x, double y)
{ return x * y; }

double Div(double x, double y)
{ return x / y; }

// Array of 5 pointers to functions that take two double parameters
// and return a double:

// double (*funcTable[5])(double, double)
//          = { Add, Sub, Mul, Div, pow };       // Initializer list.

typedef double func_t(double, double);    // The functions' type is now named func_t.
func_t *funcTable[5] = {Add, Sub, Mul, Div, pow};

// An array of pointers to strings for output:
char *msgTable[5] = {"Sum", "Difference", "Product", "Quotient", "Power"};

int main()
{
   int i;                           // An index variable.
   double x = 0, y = 0;

   printf("Enter two operands for some arithmetic:\n");
   if (scanf("%lf %lf", &x, &y) != 2)
   {
      printf("Invalid input.\n");
   }

   for (i = 0; i < 5; ++i)
   {
      printf("%10s: %6.2f\n", msgTable[i], funcTable[i](x, y));
   }

   return EXIT_SUCCESS;
}
