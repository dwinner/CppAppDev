/**
 * Член типа гибкого массива
 */

#include <stdio.h>
#include <stdlib.h>

struct flex
{
   size_t count;
   double average;
   double scores[];  // член с типом гибкого массива
};

void showFlex(const struct flex *p);

int main()
{
   struct flex *pf1, *pf2;
   size_t n = 5;
   int i;
   int tot = 0;

   // выделение памяти для структуры и массива
   pf1 = malloc(sizeof(struct flex) + n * sizeof(double));
   pf1->count = n;
   for (i = 0; i < n; i++)
   {
      pf1->scores[i] = 20.0 - i;
      tot += pf1->scores[i];
   }

   pf1->average = (double) tot / n;
   showFlex(pf1);

   n = 9;
   tot = 0;
   pf2 = malloc(sizeof(struct flex) + n * sizeof(double));
   pf2->count = n;
   for (i = 0; i < n; i++)
   {
      pf2->scores[i] = 20.0 - i / 2.0;
      tot += pf2->scores[i];
   }

   pf2->average = (double) tot / n;
   showFlex(pf2);
   free(pf1);
   free(pf2);

   return EXIT_SUCCESS;
}

void showFlex(const struct flex *restrict p)
{
   int i;
   printf("Ratings: ");
   for (i = 0; i < p->count; i++)
      printf("%g ", p->scores[i]);
   printf("\nAverage value: %g\n", p->average);
}
