/**
 * Using standart qsort function to sort groups of numbers
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM 40

void fillArray(double array[], int n);

void showArray(const double array[], int size);

int mycomp(const void *p1, const void *p2);

int main()
{
   double vals[NUM];
   fillArray(vals, NUM);
   puts("Random list:");
   showArray(vals, NUM);
   qsort(vals, NUM, sizeof(double), mycomp);
   puts("\nSorted list:");
   showArray(vals, NUM);

   return EXIT_SUCCESS;
}

void fillArray(double *array, int n)
{
   int index;

   for (index = 0; index < n; index++)
   {
      array[index] = (double) rand() / ((double) rand() + 0.1);
   }
}

void showArray(const double *array, int size)
{
   int index;

   for (index = 0; index < size; index++)
   {
      printf("%9.4f ", array[index]);

      if (index % 6 == 5)
      {
         putchar('\n');
      }
   }

   if (index % 6 != 0)
   {
      putchar('\n');
   }
}

/**
 * Sort by increasing value
 * @param p1 First pointer to value to be compared
 * @param p2 Second pointer to value to be compared
 * @return 1 if *p1 > *p2, 0 if *p1 = *p2, -1 if *p1 < *p2
 */
int mycomp(const void *p1, const void *p2)
{
   /* need to use pointers to double to access values */
   const double *a1 = (const double *) p1;
   const double *a2 = (const double *) p2;

   return *a1 < *a2 ? -1 : *a1 == *a2 ? 0 : 1;
}
