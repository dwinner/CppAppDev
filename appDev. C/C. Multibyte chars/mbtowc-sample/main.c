// mbtowc_ex.c : mbtowc() example
// -------------------------------------------------------------
// int mbtowc( wchar_t * restrict wc,
//             const char * restrict s,
//             size_t maxsize );

#include <stdlib.h>
#include <locale.h>
#include <stdio.h>

int main()
{
   int i = 0, n = 0;
   wchar_t wc;
   char mbstring[256] = "This is originally a multibyte string.\n";

   printf("The current locale is %s.\n", setlocale(LC_CTYPE, ""));
   while ((n = mbtowc(&wc, &mbstring[i], MB_CUR_MAX)) != 0)
   {
      if (n == -1)
      {
         fputs("Encoding error in multibyte string", stderr);
         break;
      }

      printf("%lc", (wint_t) wc);
      i += n;
   }

   return 0;
}
