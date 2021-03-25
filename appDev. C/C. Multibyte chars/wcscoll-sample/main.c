// wcscoll_ex.c : wcscoll() example
// -------------------------------------------------------------
// int wcscoll( const wchar_t *s1, const wchar_t *s2 );

#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
   wchar_t *samples[] = {L"anejo", L"añeja",};

   setlocale(LC_COLLATE, "es_US.UTF-8");

   int result = wcscoll(samples[0], samples[1]);

   wprintf(L"In the locale %s, ", setlocale(LC_COLLATE, NULL));

   if (result == 0)
   {
      wprintf(L"the wide strings \"%ls\" and \"%ls\" are alphabetically "
              "equivalent.\n", samples[0], samples[1]);
   }
   else if (result < 0)
   {
      wprintf(L"the wide string \"%ls\" precedes \"%ls\" "
              "alphabetically.\n", samples[0], samples[1]);
   }
   else if (result > 0)
   {
      wprintf(L"the wide string \"%ls\" comes after \"%ls\" "
              "alphabetically.\n", samples[0], samples[1]);
   }

   return 0;
}
