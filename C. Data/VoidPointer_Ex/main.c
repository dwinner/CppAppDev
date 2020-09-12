// Example 4-1. A comparison function for qsort()
// voidPointer.c

#include <stdlib.h>
#include <math.h>

#define ARR_LEN 20

/**
 * Point structure
 */
struct point
{
   float x;
   float y;
};

/**
 * Point structure
 */
typedef struct point Point;

/**
 * A function to compare any two point elements,
 * for use as a call-back function by qsort().
 * Arguments are passed by pointer.
 *
 * Returns: -1 if the first is less than the second;
 * 0 if the elements are equal;
 * 1 if the first is greater than the second.
 */
int pointCmp(const void *p1, const void *p2)
{
   Point point1 = *(Point *) p1,
      point2 = *(Point *) p2;

   float distance1 = sqrtf(powf(point1.x, 2) + powf(point1.y, 2));
   float distance2 = sqrtf(powf(point2.x, 2) + powf(point2.y, 2));

   return (distance1 < distance2) ? -1 : ((distance1 == distance2) ? 0 : 1);
}

/**
 * The main() function sorts an array of float, using the 
 * standard function qsort() with the following prototype:
 * void qsort( void *array, size_t n, size_t element_size,
 *             int (*compare)(const void *, const void *) );
 */
#include <stdio.h>
#include <time.h>

int main()
{
   /* Allocate space for the array dynamically: */
   Point *pPoints = malloc(ARR_LEN * sizeof(Point));

   /* ... Handle errors, initialize array elements ... */
   if (pPoints == NULL)
   {
      fprintf(stderr, "Insufficient memory.\n");
      exit(EXIT_FAILURE);
   }

   srand((unsigned) time(NULL));

   for (int i = 0; i < ARR_LEN; ++i)
   {
      // random numbers
      pPoints[i].x = (rand() - RAND_MAX / 2) * (100.0F / RAND_MAX);
      pPoints[i].y = (rand() - RAND_MAX / 2) * (100.0F / RAND_MAX);
   }

   /* Sort the array: */
   qsort(pPoints, ARR_LEN, sizeof(Point), pointCmp);

   /* ... Work with the sorted array ... */
   for (int i = 0; i < ARR_LEN; ++i)   // The sorted array
   {
      printf("(%8.2f;%8.2f)", pPoints[i].x, pPoints[i].y);
   }

   return 0;
}
