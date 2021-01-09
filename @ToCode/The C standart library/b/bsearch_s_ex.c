// bsearch_s_ex.c : bsearch_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__  1
#include <stdlib.h>
// void *bsearch_s( const void *key, const void *array, rsize_t n,
//                  rsize_t size,
//                  int (*compare)(const void *k, const void *el, void *context),
//                  void *context);

#include <stdio.h>

typedef struct { unsigned long id;
                 const char* value;
               } record;

int main(void)
{
   // Declaration of the comparison function:
   int cmp(const void *r1, const void *r2, void *ct);

    record data[] = { {1789,"George"}, {1809,"James"},
                      {1797,"John"}, {1801,"Thomas"} };
    size_t datacount = sizeof(data) / sizeof(data[0]);
    record querykey = { .id=1801 };
    record *found = NULL;

    // Sort the array:
    qsort_s( data, datacount, sizeof(data[0]), cmp, NULL );

    // Search the array:
    found = bsearch_s( &querykey, data, datacount, sizeof(data[0]), cmp, NULL );

    if( found == NULL )
       printf( "No record with the ID %lu found.\n", querykey.id );
    else
       printf( "The record %lu contains the value %s.\n",
               querykey.id, found->value );
} // End of main().

int cmp(const void *r1, const void *r2, void *ct)
// Compares the IDs of the records, not their data values.
// The context parameter ct is not used here.
{
    const record *p1 = (const record *)r1;
    const record *p2 = (const record *)r2;

    if      ( p1->id <  p2->id )  return -1;
    else if ( p1->id == p2->id )  return  0;
    else                          return  1;
}
