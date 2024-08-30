// wcstombs_ex.c : wcstombs() example
// -------------------------------------------------------------
// size_t wcstombs( char * restrict dest,
//                  const wchar_t * restrict src,
//                  size_t n );

#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
   if (setlocale(LC_ALL, "") == NULL)
   {
      fputs("Unable to set the locale.\n", stderr);
   }

   wchar_t fmt_amount[128] = {L'\0'};
   wchar_t prefix[32] = L"-";
   wchar_t suffix[32] = L"€";
   wchar_t number[128] = L"123.456,78";
   char output_amount[256];

   wcscpy(fmt_amount, prefix);
   wcscat(fmt_amount, number);
   wcscat(fmt_amount, suffix);

   if (-1 != wcstombs(output_amount, fmt_amount, 256))
   {
      printf("Full amount: %s\n", output_amount);
   }

   return 0;
}
