// wcscpy_ex.c : wcscpy(), wcscpy_s() example
// -------------------------------------------------------------
// wchar_t *wcscpy(wchar_t * restrict dest,
//                 const wchar_t * restrict src);
// errno_t wcscpy_s(wchar_t * restrict dest,
//                  rsize_t destmax,
//                  const wchar_t * restrict src);

#define __STDC_WANT_LIB_EXT1__ 1   // for wcscpy_s()

#include <wchar.h>
#include <stdio.h>

int main()
{
   struct record
   {
      wchar_t name[64];
      int age;
      _Bool male, smoking, discount;
   } this;
   int results;

   wprintf(L"Last name: ");
   results = wscanf(L"%63l[^\n]", this.name);

   if (results < 1)
   {
      wcscpy(this.name, L"[Name not available]");
   }
   // or:
   // wcscpy_s( this.name, sizeof(this.name)/sizeof(wchar_t),
   //           L"[Name not available]" );

   wprintf(L"%ls\n", this.name);

   return 0;
}
