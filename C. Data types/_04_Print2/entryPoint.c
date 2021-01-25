#include <stdio.h>

int main(void)
{
   unsigned int un = 3000000000; /* система с 32-битным типом int */
   short end = 200;  /* и 16-битным типом short */
   long big = 65537;
   long long verybig = 12345678908642;

   printf("un = %u, but not %d\n", un, un);
   printf("end = %hd and %d\n", end, end);
   printf("big = %ld, but not %hd\n", big, big);
   printf("verybig = %lld, but not %ld\n", verybig, verybig);

   getchar();
   return 0;
}
