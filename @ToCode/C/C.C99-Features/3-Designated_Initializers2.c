// Fig. E.4: figE_04.c
// Using designated initializers to initialize an array of structs in C99
#include <stdio.h>

struct twoInt // declare a struct of two integers
{
   int x;
   int y;
}; 

int main(void)
{
   // explicitly initialize elements of array a
   // then, explicitly initialize two elements 
   struct twoInt a[5] =
   {
      [0] = {.x = 1, .y = 2},
      [4] = {.x = 10, .y = 20}
   };

   // output array contents
   printf("x\ty\n");

   for (size_t i = 0; i < 5; ++i) {
      printf("%d\t%d\n", a[i].x, a[i].y);
   } 
}
