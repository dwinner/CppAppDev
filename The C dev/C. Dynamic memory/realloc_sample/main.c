// realloc_ex.c : realloc() example
// -------------------------------------------------------------

#include <stdlib.h>       // void *realloc( void *ptr, size_t n );
#include <stdio.h>

int main()
{
   typedef struct
   {
      int len;
      float array[];
   } DynArray_t;

   DynArray_t *daPtr = malloc(sizeof(DynArray_t) + 10 * sizeof(float));
   if (daPtr == NULL)
   {
      return -1;
   }

   daPtr->len = 10;
   for (int i = 0; i < daPtr->len; ++i)
   {
      daPtr->array[i] = 1.0F / (i + 1);
   }

   /* daPtr->array[10] = 0.1F               // Invalid array index! */

   DynArray_t *daResizePtr = realloc(daPtr,
                                     sizeof(DynArray_t) + 11 * sizeof(float));
   if (daResizePtr != NULL)
   {
      daPtr = daResizePtr;
      daPtr->len = 11;
      daPtr->array[10] = 0.1F / 12;         // OK now.
   }
   else
   {
      /* We'll just have to get along with the array of 10 floats.
      ...   */
      return -1;
   }

   for (int i = 0; i < daPtr->len; ++i)
   {
      printf("%2d : %8f\n", i, daPtr->array[i]);
   }

   return 0;
}
