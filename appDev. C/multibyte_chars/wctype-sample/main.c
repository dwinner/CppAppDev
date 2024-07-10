// wctype_ex.c : wctype() example
// -------------------------------------------------------------
// wctype_t wctype( const char *property );

#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main()
{
   wctype_t wct_kanji, wct_kata, wct_hira  /* , ... */ ;

   if (setlocale(LC_CTYPE, "ja_JP.UTF-8") == NULL)
   {
      fputws(L"Unable to set the locale.\n", stderr);
   }

   if ((wct_kata = wctype("jkata")) == 0)
   {
      wprintf(L"The locale doesn't support the wide-character type "
              "string \"jkata\".\n");
      return -1;
   }

   /* ... */
   wchar_t wc = fgetwc(stdin);
   if (iswctype(wc, wct_kata))
   {          // Mainly 0xFF66 − 0xFF9F.
      wprintf(L"%lc is a katakana character.\n", wc);
   }
   else
   {
      wprintf(L"%lc is a not katakana character.\n", wc);
   }

   return 0;
}
