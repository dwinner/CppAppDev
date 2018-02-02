/**
 *	Prints integer in binary form
 */

#include <stdio.h>

void toBinary(unsigned long n);

int main()
{
   unsigned long number;
   printf("Enter an integer (q to quit):\n");
   while (scanf_s("%ul", &number) == 1)
   {
      printf("Binary equivalent: ");
      toBinary(number);
      putchar('\n');
      printf("Enter an integer (q to quit):\n");
   }

   printf("Done.\n");

   return 0;
}

/**
 * @brief Transform integer to binary format
 *		@param n integer number
 */
void toBinary(const unsigned long n)
{
   const int r = n % 2;

   if (n >= 2)
   {
      toBinary(n / 2);
   }

   putchar('0' + r);
}
