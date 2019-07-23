/**
 * Armstrong number
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/**
 * Compute the count of digits in number
 * @param number Number
 * @return Count of digits
 */
int computeDigitCount(int number);

/**
 * Finds out whether the number is Armstrong or not
 * @param number Number
 * @example 1634 = 1^4 + 6^4 + 3^4 + 4^4, 153 = 1^3 + 5^3 + 3^3
 * @return true if the number is Armstrong number, false - otherwise
 */
bool isArmstrongNumber(int number);

int main()
{
   int number;

   printf("Enter the number: ");
   scanf("%d", &number);

   printf(isArmstrongNumber(number)
          ? "%d - Armstrong number\n"
          : "%d - is not Armstrong number\n", number);

   return EXIT_SUCCESS;
}

int computeDigitCount(int number)
{
   int digitCount = 0;

   while (number != 0)
   {
      number /= 10;
      ++digitCount;
   }

   return digitCount;
}

bool isArmstrongNumber(int number)
{
   int digitCount = computeDigitCount(number);
   int originalNumber = number;
   int remainder;
   int result = 0;

   while (originalNumber != 0)
   {
      remainder = originalNumber % 10;
      result += pow(remainder, digitCount);
      originalNumber /= 10;
   }

   return result == number;
}
