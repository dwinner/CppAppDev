// wcschr_ex.c : wcschr() example
// -------------------------------------------------------------
// wchar_t *wcschr( const wchar_t *s, wchar_t c );

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   wchar_t street[32];
   wchar_t city[32];
   wchar_t state_province[32];
   wchar_t zip[16];
} Address;

wchar_t print_addr[128] = L"720 S. Michigan Ave.\nChicago, IL 60605\n";

int main()
{
   int sub_length;
   Address *newAddr = calloc(1, sizeof(Address));

   if (newAddr != NULL)
   {
      sub_length = wcschr(print_addr, L'\n') - print_addr;
      wcsncpy(newAddr->street, print_addr,
              (sub_length < 31 ? sub_length : 31));
      /* ... */
      fputws(newAddr->street, stdout);
   }

   return 0;
}
