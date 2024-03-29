// wcsftime_ex.c : wcsftime() example
// -------------------------------------------------------------
// size_t wcsftime( wchar_t * restrict s, size_t n,
//                  const wchar_t * restrict format,
//                  const struct tm * restrict timeptr );

#include <time.h>
#include <wchar.h>
#include <stdio.h>

#define MAX_HDR 1024

int main()
{
   time_t now;
   struct tm *localnow;
   wchar_t hdr_date[MAX_HDR] = L"";

   time(&now);
   localnow = localtime(&now);

   if (wcsftime(hdr_date, MAX_HDR, L"Date: %a, %d %b %Y %T %z", localnow))
   {
      fputws(hdr_date, stdout);
   }
   else
   {
      return -1;
   }

   return 0;
}
