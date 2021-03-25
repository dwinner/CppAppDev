// wcrtomb_s_ex.c : wcrtomb_s() example
// -------------------------------------------------------------
// errno_t wcrtomb_s( size_t * restrict retval,
//                    char * restrict dest, rsize_t destmax,
//                    wchar_t wc, mbstate_t * restrict ps);

#define __STDC_WANT_LIB_EXT1__ 1

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int main()
{
   if (setlocale(LC_ALL, "") == NULL)
   {
      fputs("Unable to set the locale.\n", stderr);
   }

   printf("\nThe current locale is '%s'.\n", setlocale(LC_CTYPE, NULL));

   wchar_t wc = L'\u00b1';     //'±'
   char mbStr[MB_CUR_MAX];
   size_t nBytes = 0;
   mbstate_t state = {0};

   if (wcrtomb_s(&nBytes, mbStr, sizeof(mbStr), wc, &state) != 0)
   { /* Handle the error ... */
      fputs("Error ...", stderr);
      return -1;
   }

   printf("Character: '%lc'; multibyte code:", wc);     // '±'
   for (unsigned i = 0; i < nBytes; ++i)
   {
      printf(" %#04x", (unsigned char) mbStr[i]);
   }       // 0xc2 0xb1

   putchar('\n');

   return 0;
}
