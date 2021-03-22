/**
 * Pointer version of the selection_sortf() function
 * With gcc use the option -O
 * GCC does not inline any functions when not optimizing
 */

#include <stdio.h>
#include "selection_sort.h"

int main()
{
   float fArr[] = {2.2F, 0.0F, -1.1F, 3.3F, -4.4F};
   int n = sizeof(fArr) / sizeof(*fArr);

   selection_sortf(fArr, n);

   for (int i = 0; i < n; ++i)
   {
      printf("%8.2f", fArr[i]);
   }

   putchar('\n');
   return 0;
}
