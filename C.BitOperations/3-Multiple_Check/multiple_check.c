/**
 * This program determines whether a value is a multiple of X.
 */
#include <stdio.h>

int multiple(int num);

int main(void)
{
   int y;
   scanf_s("%d", &y);

   printf(multiple(y)
             ? "%d is a multiple of X\n"
             : "%d is not a multiple of X\n",
          y);

   return 0;
}

/**
 * \brief Determine whether num is a multiple of X
 * \param num Number
 * \return 1 if true, 0 - false
 */
int multiple(const int num)
{
   int mask = 1; // initialize mask
   int mult = 1; // initialize mult

   for (int i = 1; i <= 10; ++i, mask <<= 1)
   {
      if ((num & mask) != 0)
      {
         mult = 0;
         break;
      }
   }

   return mult;
}
