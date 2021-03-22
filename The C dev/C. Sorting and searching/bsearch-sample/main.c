/**
 * bsearch() example:
 * void *bsearch( const void *key, const void *array, size_t n, size_t size, int (*compare)(const void *, const void *));
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
   unsigned long id;
   int data;
} record;

int main()
{
   // Declare comparison function:
   int id_cmp(const void *s1, const void *s2);

   record recordSet[] =
       {
           {3, 5},
           {5, -5},
           {4, 10},
           {2, 2},
           {1, -17}
       };
   record queryKey;
   record *found = NULL;
   int recordCount = sizeof(recordSet) / sizeof(record);

   printf("Query record number: ");
   scanf("%lu", &queryKey.id);

   printf("\nRecords before sorting:\n\n"
          "%8s %8s %8s\n", "Index", "ID", "Data");

   for (int i = 0; i < recordCount; i++)
   {
      printf("%8d %8lu %8d\n",
             i,
             recordSet[i].id,
             recordSet[i].data);
   }

   qsort(recordSet, recordCount, sizeof(record), id_cmp);

   printf("\nRecords after sorting:\n\n"
          "%8s %8s %8s\n", "Index", "ID", "Data");
   for (int i = 0; i < recordCount; i++)
   {
      printf("%8d %8lu %8d\n",
             i,
             recordSet[i].id,
             recordSet[i].data);
   }

   found = (record *) bsearch(&queryKey, recordSet, recordCount, sizeof(record), id_cmp);
   if (found == NULL)
   {
      printf("No record with the ID %lu found.\n", queryKey.id);
   }
   else
   {
      printf("The data value in record %lu is %d.\n",
             queryKey.id, found->data);
   }

}

/**
 * Compares records by ID, not data content.
 * @param s1 1st record pointer
 * @param s2 2nd record pointer
 * @return -1 if id1 &lt; id2, 0 if equals, 1 if id1 &gt; id2
 */
int id_cmp(const void *s1, const void *s2)
{
   record *p1 = (record *) s1;
   record *p2 = (record *) s2;

   return p1->id >= p2->id
          ? p1->id == p2->id
            ? 0
            : 1
          : -1;
}
