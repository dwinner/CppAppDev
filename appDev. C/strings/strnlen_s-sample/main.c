// strnlen_s_ex.c : strnlen_s() example
// -------------------------------------------------------------
// For the secure functions.
// size_t strnlen_s(const char *s, size_t maxsize);

#define __STDC_WANT_LIB_EXT1__ 1

#include <string.h>
#include <stdio.h>

int main()
{
   char str[] = "hello";

   size_t len = strnlen_s(str, 1000);  // len = 5

   if (strnlen_s(str, 4) == 4)
   {
      puts("str is more than 4 characters long.");
   }

   return 0;
}
