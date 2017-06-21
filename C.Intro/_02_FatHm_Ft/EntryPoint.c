// Преобразует две морских сажени в футы

#include <stdio.h>

int main(void)
{
   int feet, fathoms;
   fathoms = 2;
   feet = 6 * fathoms;
   printf("In %d sea mt contains %d foots!\n", fathoms, feet);
   printf("Yes, exactly %d foots\n", 6 * fathoms);
   getchar();

   return 0;
}
