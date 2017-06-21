/* Программа, в которой используются две функции в одном файле */
#include <stdio.h>

void butler(void); /* Прототип функции в стандарте ISO */

int main(void)
{
   printf("I'm calling door-man.\n");
   butler();
   printf("Yes. Get me a cup of tea and writing CD's\n");
   getchar();

   return 0;
}

void butler(void)
{
   printf("Have you called, sir?\n");
}
