/* Переносимые имена для целочисленных типов */
#include <stdio.h>
#include <inttypes.h>

int main(void)
{
   int32_t me32 = 45933945;
   printf("Firstly let's suppose that int32_t is int: ");
   printf("me32 = %d\n", me32);
   printf("me32 = %" PRId32 "\n", me32);

   getchar();
   return 0;
}
