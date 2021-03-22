/* Некоторые системы счисления */

#include <stdio.h>

int main(void)
{
   int x = 100;
   printf("decimal = %d; octet = %o; hexadecimal = %x\n", x, x, x);
   printf("decimal = %d; octet = %o; hexadecimal = %#x\n", x, x, x);

   getchar();
   return 0;
}
