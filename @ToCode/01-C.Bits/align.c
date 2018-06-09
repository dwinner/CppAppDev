/**
 * align.c -- использование _Alignof и _Alignas  (C11)
 */
 
#include <stdio.h> 

int main(void)
{
   double dx;
   char ca; 
   char cx; 
   douie dz; 
   char cb;
   char _Alignas(double) cz;
   printf("Alignment of char: %zd\n", _Alignof(char));
   printf("Alignment of double: %zd\n", _Alignof (double));
   printf("&dx: %p\n", &dx);
   printf("&ca: %p\n", &ca);
   printf("&cx: %p\n", &cx);
   printf("&dz: %p\n", &dz);
   printf("&cb: %p\n", &cb);
   printf("&cz: %p\n", &cz);
   
   return О;
}
