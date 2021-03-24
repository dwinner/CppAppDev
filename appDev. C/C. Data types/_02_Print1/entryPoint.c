/* Некоторые свойства функции printf() */

#include <stdio.h>

int main(void)
{
   int ten = 10;
   int two = 2;

   printf("Right execution: ");
   printf("%d minus %d is equal %d\n", ten, two, ten - two);

   getchar();
   return 0;
}
