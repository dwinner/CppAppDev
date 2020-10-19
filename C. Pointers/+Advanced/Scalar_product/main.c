// Example 9-3. The function scalar_product()
// scalarProduct.c

// This function calculates the scalar product of two arrays.
// Arguments: Two arrays of double, and their length.
//            The two arrays need not be distinct.

double scalar_product(const double *restrict p1,
                      const double *restrict p2,
                      int n)
{
   double result = 0.0;

   for (int i = 0; i < n; ++i)
   {
      result += p1[i] * p2[i];
   }

   return result;
}

#include <stdio.h>

int main()
{
   double arr1[] = {1.1, 2.2, 3.3, 4.4};
   int len = sizeof(arr1) / sizeof(*arr1);

   for (int i = 0; i < len; ++i)
   {
      printf("%8.2f", arr1[i]);
   }

   putchar('\n');

   double sp = scalar_product(arr1, arr1, len);

   printf("The scalar product of this array with itself is %.2f\n", sp);

   return 0;
}
