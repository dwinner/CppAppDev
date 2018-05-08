/**
 * Using designated initializers to initialize an array
 * of structs in C99
 */

#include <stdio.h>

struct twoInt
{
   int x;
   int y;
};

int main()
{
   struct twoInt a[5] =
      {
         [0]={.x=1, .y=2},
         [4]={.x=10, .y=20}
      };

   printf("x\ty\n");

   for (int i = 0; i < 5; ++i)
   {
      printf("%d\t%d\n", a[i].x, a[i].y);
   }

   return 0;
}