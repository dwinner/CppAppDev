/**
 * Is prime number
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int n);

int main()
{
   int n, flag = 0;

   printf("Enter the positive integer value: ");
   scanf("%d", &n);

   flag = isPrime(n);

   printf(flag == 0
          ? "%d - prime\n"
          : "%d - is not prime\n", n);

   return EXIT_SUCCESS;
}

bool isPrime(int n)
{
   bool isPrime = false;

   for (int i = 2; i <= n / 2; ++i)
   {
      if (n % i == 0)
      {
         isPrime = true;
         break;
      }
   }

   return isPrime;
}