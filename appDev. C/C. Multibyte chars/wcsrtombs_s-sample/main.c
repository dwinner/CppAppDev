// wcsrtombs_s_ex.c : wcsrtombs_s() example
// -------------------------------------------------------------
// errno_t wcsrtombs_s(size_t * restrict retval,
//                     char * restrict dest,
//                     rsize_t destmax,
//                     const wchar_t ** restrict src,
//                     rsize_t n,
//                     mbstate_t * restrict state);

#define __STDC_WANT_LIB_EXT1__ 1

#include <wchar.h>
#include <locale.h>
#include <stdio.h>

int main()
{
   if (setlocale(LC_ALL, "") == NULL)
   {
      fputs("Unable to set the locale.\n", stderr);
   }

   wchar_t widestr[] = L"A wide-character string ...";
   const wchar_t *wcptr = widestr;     // A pointer to a wide character.
   char mbstr[100] = "";               // For the multibyte string.
   size_t mblen = 0;
   mbstate_t mbstate = {0};            // Conversion state.

   if (wcsrtombs_s(&mblen, mbstr, sizeof(mbstr),
                   &wcptr, 3, &mbstate) == 0)
   {
      printf("Multibyte length: %zu; character codes: [", mblen);
      for (size_t i = 0; i < mblen; ++i)
      {
         printf(" %X", (unsigned char) mbstr[i]);
      }

      puts(" ]");

      if (wcptr != NULL)
      {
         printf("Wide characters remaining: \"%ls\"\n", wcptr);
      }
   }

   return 0;
}
