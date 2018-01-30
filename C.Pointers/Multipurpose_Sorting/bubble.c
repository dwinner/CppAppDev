#include <stddef.h>

void bubble(int work[], const size_t size, int (*compare)(int a, int b))
{
   void swap(int* element1Ptr, int* element2Ptr);

   // loop to control passes
   for (unsigned int pass = 1; pass < size; ++pass)
   {
      // loop to control tne number of comparisons per pass
      for (size_t count = 0; count < size - 1; ++count)
      {
         // if adjacent elements are out of order, swap them
         if ((*compare)(work[count], work[count + 1]) > 0)
         {
            swap(&work[count], &work[count + 1]);
         }
      }
   }
}

int ascending(const int a, const int b)
{
   return b < a;
}

int descending(const int a, const int b)
{
   return b > a;
}

static void swap(int* element1Ptr, int* element2Ptr)
{
   const int hold = *element1Ptr;
   *element1Ptr = *element2Ptr;
   *element2Ptr = hold;
}
