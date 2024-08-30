// Example 7-3. Function factorial()
// factorial.c

#include <stdio.h>

long double factorial( register unsigned int n);

int main()
{
   printf("The factorial  5! = %.0Lf\n", factorial(5) );
   printf("The factorial 20! = %.0Lf\n", factorial(20) );
   return 0; 
}

// factorial() calculates n!, the factorial of a non-negative number n.
// For n > 0, n! is the product of all integers from 1 to n inclusive.
// 0! equals 1.
// Argument: A whole number, with type unsigned int.
// Return value: The factorial of the argument, with type long double.

long double factorial( register unsigned int n )
{
   long double f = 1;
   while ( n > 1 )
     f *= n--;
   return f;
}
