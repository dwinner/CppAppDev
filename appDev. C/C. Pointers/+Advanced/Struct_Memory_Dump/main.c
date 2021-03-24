/**
 * Вывод шестнадцатиричного дампа структурной переменной
 */

#include <stdio.h>
#include <stdlib.h>

struct Data
{
   short id;
   double val;
};

int main()
{
   struct Data myData = {0x123, 77.7};   // Инициализация структуры

   unsigned char *cp = (unsigned char *) &myData;  // Указатель на первый байт структуры

   printf("%p: ", cp);  // Вывод начального адреса

   // Шестнадцатиричный вывод каждого байта структуры
   for (int i = 0; i < sizeof(myData); ++i)
   {
      printf("%02X ", *(cp + i));
   }

   return EXIT_SUCCESS;
}
