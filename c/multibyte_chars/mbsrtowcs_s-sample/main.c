// mbsrtowcs_s_ex.c : mbsrtowcs_s() example
// -------------------------------------------------------------
// errno_t mbsrtowcs_s(size_t * restrict retval,
//                     wchar_t * restrict dst,
//                     size_t dstmax,
//                     const char ** restrict src,
//                     size_t n,
//                     mbstate_t * restrict state );

#define __STDC_WANT_LIB_EXT1__ 1

#include <wchar.h>
#include <stdio.h>

int main()
{
   const char *mbptr = "Any multibyte string";
   wchar_t wcstr[10];            // A buffer for wide characters
   size_t len;                   // and its capacity.
   mbstate_t state = {0};

   if (mbsrtowcs_s(&len, wcstr, 10, &mbptr, 9, &state) != 0)
   {
      printf("The array contains an invalid multibyte character.\n");
   }
   else
   {
      printf("Length: %zu; text: %ls\n", len, wcstr);
      printf("The remaining characters: %s\n", mbptr);
   }

   return 0;
}
