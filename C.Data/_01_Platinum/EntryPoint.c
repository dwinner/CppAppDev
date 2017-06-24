#include <stdio.h>

int main(void)
{
   float weight;

   printf("Enter your weight in feets");

   // Получить входные данные от пользователя
   scanf_s("%f", &weight);
   float value = 1700.0 * weight * 14.5833;
   printf("Your weight is $%.2f.\n", value);

   getchar();
   return 0;
}
