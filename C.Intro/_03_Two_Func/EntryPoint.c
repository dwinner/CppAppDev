/* ���������, � ������� ������������ ��� ������� � ����� ����� */
#include <stdio.h>

void butler(void); /* �������� ������� � ��������� ISO */

int main(void)
{
   printf("I'm calling door-man.\n");
   butler();
   printf("Yes. Get me a cup of tea and writing CD's\n");
   getchar();

   return 0;
}

void butler(void)
{
   printf("Have you called, sir?\n");
}
