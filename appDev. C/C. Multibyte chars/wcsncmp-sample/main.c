// wcsncmp_ex.c : wcsncmp() example
// -------------------------------------------------------------
// int wcsncmp( const wchar_t *s1,
//              const wchar_t *s2, size_t n );

#include <wchar.h>

int main()
{
   wchar_t *months[] =
       {
           L"January", L"February", L"March", L"April",
           L"May", L"June", L"July", L"August",
           L"September", L"October", L"November", L"December"
       };

   wchar_t date[] = L"Thu, 10 Mar 2005 13:44:18 +0100";
   int mo = 0;
   while ((mo < 12) && (wcsncmp(date + 8, months[mo], 3) != 0))
   {
      mo++;
   }

   if (mo < 12)
   {
      wprintf(L"Month: %ls\n", months[mo]);
   }

   return 0;
}
