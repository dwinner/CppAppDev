/* Отображение float двумя способами */
#include <stdio.h>

int main(void)
{
   float aboat = 32000.0;
   double abet = 2.14e9;
   long double dip = 5.32e-5;

   printf("%f can be written as %e\n", aboat, aboat);
   printf("And its %a in hex degree 2\n", aboat);
   printf("%f can be written as %e\n", abet, abet);
   printf("%Lf can be written as %Le\n", dip, dip);

   getchar();
   return 0;
}
