#include <stdio.h>
#define SIZE 5

// function prototypes
void modifyArray(int b[], const size_t size);
void modifyElement(int e);

int main(int argc, char* argv[])
{
   int a[SIZE] = {0, 1, 2, 3, 4};

   puts("Effects of passing entire array by reference:\n\nThe values of the original array are:");

   for (int i = 0; i < SIZE; ++i)
   {
      printf("%3d", a[i]);
   }

   puts("");

   modifyArray(a, SIZE);

   puts("The values of the modified array are:");

   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%3d", a[i]);
   }

   modifyElement(a[3]); // has no effect

   printf("The value of a[3] is %d\n", a[3]);

   return 0;
}

/**
 * \brief In this function "b" points to the original array "a" in memory
 * \param b Array
 * \param size Array size
 */
void modifyArray(int b[], const size_t size)
{
   for (size_t i = 0; i < size; ++i)
   {
      b[i] *= 2;
   }
}

void modifyElement(int e)
{
   printf("Value in modifyElement is %d\n", e *= 2);
}
