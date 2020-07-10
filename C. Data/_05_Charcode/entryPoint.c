#include <stdio.h>

int main(void)
{
   char ch;
   printf("Enter a symbol.\n");
   scanf("%c", &ch); /* Пользователь вводит символ */
   printf("Symbol code %c is equal to %d.\n", ch, ch);

   getchar();
   return 0;
}
