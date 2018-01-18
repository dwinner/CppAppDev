/**
 * Array functions
 */

#include <stdio.h>

#define SIZE 5

void showArray(const double ar[], int n);
void multArray(double ar[], int n, double mult);

int main(void)
{
   double dip[SIZE] = { 20.0, 17.66, 8.2, 15.3, 22.22 };

   printf("The original dip array:\n");
   showArray(dip, SIZE);
   multArray(dip, SIZE, 2.5);
   printf("The dip array after calling mult_array():\n");
   showArray(dip, SIZE);

   return 0;
}

/**
 * displays array contents
 */
void showArray(const double ar[], const int n)
{
   int i;
   for (i = 0; i < n; i++)
      printf("%8.3f ", ar[i]);
   putchar('\n');
}

/**
 * multiplies each array member by the same multiplier
 */
void multArray(double ar[], const int n, const double mult)
{
   int i;
   for (i = 0; i < n; i++)
      ar[i] *= mult;
}
