// wctomb_s_ex.c : wctomb_s() example
// -------------------------------------------------------------
// errno_t wctomb_s( int * restrict status,
//                   char * restrict s,
//                   rsize_t smax,
//                   wchar_t wc);

#define __STDC_WANT_LIB_EXT1__ 1         // For wctomb_s()

#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
   setlocale(LC_ALL, "en_US.utf8");

   wchar_t wc = L'\u03B1';       // Greek lowercase alpha α
   char mbStr[MB_CUR_MAX];
   int nBytes = 0;

   // if( (nBytes = wctomb( mbStr, wc )) < 0)
   // is equivalent to
   if (wctomb_s(&nBytes, mbStr, sizeof(mbStr), wc) != 0)
   {
      /* error: */
      return -1;
   }

   printf("Wide-character code: %#06x; character: '%lc'; "
          "multibyte code:", wc, wc);
   for (int i = 0; i < nBytes; ++i)
   {
      printf(" %#04x", (unsigned char) mbStr[i]);
   }

   putchar('\n');

   return 0;
}
