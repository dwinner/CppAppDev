// strcat_ex.c : strcat(), strcat_s() example
// -------------------------------------------------------------
// char *strcat( char * restrict s1,
//               const char * restrict s2 );
// errno_t strcat_s( char * restrict s1, rsize_t s1max,
//                   const char * restrict s2 );

#define __STDC_WANT_LIB_EXT1__ 1   // for strcat_s()

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   char last_name[32];
   char first_name[32];
   _Bool is_male;
} Name;

int main()
{
   char display_name[80];
   Name *newName = calloc(1, sizeof(Name));

   /* ... check for calloc failure; read in the name parts ... */
   if (newName == NULL)
   {
      fprintf(stderr, "Out of memory\n");
      return -1;
   }

   *newName = (Name)
       {
           "Lincoln",
           "Abraham",
           1
       };

   strcpy(display_name, (newName->is_male ? "Mr. " : "Ms. "));
   strcat(display_name, newName->first_name);
   strcat(display_name, " ");
   strcat(display_name, newName->last_name);

   // Better to use strcat_s() in case the fields in the Name
   // structure are ever enlarged:
   // strcat_s( display_name, sizeof(display_name), newName->first_name );
   // strcat_s( display_name, sizeof(display_name), " " );
   // strcat_s( display_name, sizeof(display_name), newName->last_name );

   puts(display_name);

   return 0;
}
