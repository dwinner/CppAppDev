/**
 * Creates a file records.dat with some test data
 */

#include <stdio.h>
#include <stdlib.h>
#include "record.h"

char dataFile[] = "records.dat";   // File name

int main()
{
   FILE *fp;
   Record_t records[] =
      {
         {1789L, "George"},
         {1797L, "John"},
         {0L,    "Harry"},
         {1801L, "Thomas"},
         {1809L, "James"},
         {1825L, "Quincy"}
      };

   size_t n = sizeof(records) / sizeof(*records);

   if ((fp = fopen(dataFile, "wb")) == NULL)
   {
      fprintf(stderr, "Error on opening output file \"%s\".\n", dataFile);
      return EXIT_FAILURE;
   }

   if (fwrite(records, sizeof(Record_t), n, fp) < n)
   {
      fprintf(stderr, "Error on writing to output file \"%s\".\n", dataFile);
      return EXIT_FAILURE;
   }

   printf("%d records written.\n", n);

   return EXIT_SUCCESS;
}
