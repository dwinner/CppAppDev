/**
 * Usage of _Alignof and _Alignas
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
   double dx;
   char ca;
   char cx;
   double dz;
   char cb;
   char _Alignas(double) cz;

   printf("Alignment of char: %d\n", _Alignof(char));
   printf("Alignment of double: %d\n", _Alignof(double));
   printf("&dx: %p\n", &dx);
   printf("&ca: %p\n", &ca);
   printf("&cx: %p\n", &cx);
   printf("&dz: %p\n", &dz);
   printf("&cb: %p\n", &cb);
   printf("&cz: %p\n", &cz);

   return EXIT_SUCCESS;
}