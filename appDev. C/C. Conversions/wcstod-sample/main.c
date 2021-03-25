// wcstod_ex.c : wcstod() example
// -------------------------------------------------------------
// double wcstod( const wchar_t * restrict wcs,
//                wchar_t ** restrict endptr );
// float wcstof( const wchar_t * restrict wcs,
//               wchar_t ** restrict endptr );
// long double wcstold( const wchar_t * restrict wcs,
//                      wchar_t ** restrict endptr );

#include <wchar.h>
#include <stdio.h>

int main()
{
   wchar_t in[1024], *this = in, *next = in;
   double val;

   fputws(L"Enter some floating-point numbers, please:\n", stdout);
   wscanf(L"%l[^\n]", in);

   fputws(L"Here are the values you entered:\n", stdout);
   while (1)
   {
      val = wcstod(this, &next);
      if (next == this)
      {           // Means no conversion possible.
         break;
      }

      this = next;
      wprintf(L"\t%g\n", val);
   }

   fputws(L"Done.\n", stdout);

   return 0;
}
