/* ”правл€ющие последовательности */
#include <stdio.h>

int main(void)
{
   float salary;
   printf("\aEnter the desired sum of a month's salary");
   printf(" $________\b\b\b\b\b\b\b");
   scanf("%f", &salary);
   printf("\n\t$%.2f in month is $%.2f in year.", salary, salary * 12.0);
   printf("\rOah\n");

   getchar();
   return 0;
}
