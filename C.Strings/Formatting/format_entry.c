/**
 * Formatting a string
 */
#include <stdio.h>
#define MAX 20

int main(void)
{
   char first[MAX];
   char last[MAX];
   char formal[2 * MAX + 10];
   double prize;

   puts("Enter your first name:");
   gets_s(first, MAX);
   puts("Enter your last name:");
   gets_s(last, MAX);
   puts("Enter your prize money:");
   scanf_s("%lf", &prize);
   sprintf_s(formal, 2 * MAX + 10, "%s, %-19s: $%6.2f\n",
      last, first, prize);
   puts(formal);
   
   return 0;
}
