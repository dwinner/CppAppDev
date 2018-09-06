/**
 * Анонимные структуры
 */

#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN  20

struct person
{
   int id;
   struct
   {
      char first[NAME_LEN];
      char last[NAME_LEN];
   };
};

int main()
{
   struct person ted = {8483, {"Ted", "Grass"}};
   printf("Id: %d\n", ted.id);
   printf("Name: %s\n", ted.first);
   printf("Last name: %s\n", ted.last);

   return EXIT_SUCCESS;
}