/**
 * Reading characters and strings
 */
#include <stdio.h>

int main(void)
{
   char x;
   char y[9];

   printf("%s", "Enter a string: ");
   scanf_s("%c%8s", &x, y);

   puts("The input was:");
   printf("the character \"%c\" and the string \"%s\"\n", x, y);

   return 0;
}
