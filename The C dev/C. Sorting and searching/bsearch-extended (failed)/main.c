/**
 * Extended binary search - by context:
 * void *bsearch_s( const void *key, const void *array, rsize_t n,
 *                  rsize_t size,
 *                  int (*compare)(const void *k, const void *el, void *context),
 *                  void *context);
 */

#define __STDC_WANT_LIB_EXT1__  1

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
   unsigned long id;
   const char* value;
} record;

int main(void)
{
   // Declaration of the comparison function:
   int cmp(void* r1, const void* r2, const void* ct);

   record data[] =
   {
      {1789, "George"},
      {1809, "James"},
      {1797, "John"},
      {1801, "Thomas"}
   };

   const size_t dataCount = sizeof data / sizeof data[0];
   record queryKey = {.id = 1801};
   record* found = NULL;

   // Sort the array:
   qsort_s(data, dataCount, sizeof data[0], cmp, NULL);

   // Search the array:
   found = bsearch_s(&queryKey, data, dataCount, sizeof data[0], cmp, NULL);

   if (found == NULL)
   {
      printf("No record with the ID %lu found.\n",
             queryKey.id);
   }
   else
   {
      printf("The record %lu contains the value %s.\n",
             queryKey.id,
             found->value);
   }

   return 0;
}

/**
 * Compares the IDs of the records, not their data values
 * @param r1 1st record pointer
 * @param r2 2nd record pointer
 * @param ct The context parameter ct is not used here
 * @return 1: r1 &gt; r2; 0: r1 = r2; -1: r1 &lt; r2 (depending on context)
 */
int cmp(void* r1, const void* r2, const void* ct)
{
   record* p1 = (record*)r1;
   const record* p2 = (const record*)r2;
   if (p1 == NULL || p2 == NULL)
   {
      return 0;
   }

   return p1->id >= p2->id ? p1->id != p2->id ? 1 : 0 : -1;
}
