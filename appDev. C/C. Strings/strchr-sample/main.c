// strchr_ex.c : strchr() example
// -------------------------------------------------------------
// char *strchr( const char *s, int c );

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   char street[32];
   char city[32];
   char state_province[32];
   char zip[16];
} Address;

char print_addr[128] = "720 S. Michigan Ave.\nChicago, IL 60605\n";

int main()
{
   int sub_length;
   Address *newAddr = calloc(1, sizeof(Address));

   if (newAddr != NULL)
   {
      sub_length = strchr(print_addr, '\n') - print_addr;
      strncpy(newAddr->street, print_addr,
              (sub_length < 31 ? sub_length : 31));
      /* ... */
      puts(newAddr->street);
   }

   return 0;
}
