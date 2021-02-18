/**
 * Finds out whether the number is palindrom
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPalindrom(int aNumber);

int main()
{
   int n;

   printf("Enter the integer number: ");
   scanf("%d", &n);

   printf(isPalindrom(n)
          ? "%d - palindrom\n"
          : "%d - not palindrom\n", n);

   return EXIT_SUCCESS;
}

/**
 * Finds out if the number is palindrom
 * @example i.e. 123321 is palindrom
 * @param aNumber Number
 * @return true, if aNumber is palindrom, false - otherwise
 */
bool isPalindrom(int aNumber)
{
   int reversedNum = 0, originalNum = aNumber, remainder;

   while (aNumber != 0)
   {
      remainder = aNumber % 10;
      reversedNum = reversedNum * 10 + remainder;
      aNumber /= 10;
   }

   return originalNum == reversedNum;
}
