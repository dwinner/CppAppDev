// wcsspn_ex.c : wcsspn() example
// -------------------------------------------------------------
// size_t wcsspn( const wchar_t *s1,
//                const wchar_t *s2 );

#include <wchar.h>
#include <stdio.h>

int main()
{
   wchar_t word_in[256];
   double val;

   fputws(L"Enter a floating-point number, please: ", stdout);
   wscanf(L"%ls", word_in);

   int index = wcsspn(word_in, L"+-0123456789eE.");
   if (index < wcslen(word_in))
   {
      wprintf(L"Sorry, but the character %lc is not permitted.\n",
              word_in[index]);
   }
   else
   {
      swscanf(word_in, L"%lg", &val);
      wprintf(L"You entered the value %g\n", val);
   }

   return 0;
}
