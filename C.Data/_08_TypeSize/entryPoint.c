/* Вывод размеров типов */
#include <stdio.h>

int main(void)
{
   printf("Type int has size: %d bytes.\n", sizeof(int));
   printf("Type char has size: %d bytes.\n", sizeof(char));
   printf("Type long has size: %d bytes.\n", sizeof(long));
   printf("Type long long has size: %d bytes.\n", sizeof(long long));
   printf("Type double has size: %d bytes.\n", sizeof(double));
   printf("Type long double has size: %d bytes.\n", sizeof(long double));

   getchar();
   return 0;
}
