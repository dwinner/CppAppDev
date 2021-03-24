// strncat_ex.c : strncat(), strncat_s() example
// -------------------------------------------------------------
// char *strncat( char * restrict s1,
//                const char * restrict s2, size_t n );
// errno_t strncat_s( char * restrict s1, rsize_t s1max,
//                    const char * restrict s2, rsize_t n);

#define __STDC_WANT_LIB_EXT1__ 1    // For the secure functions.

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
   char str1[] = "hello ",       // 7 bytes
   str2[10] = "hello ",     // 7 + 3 bytes
   str3[10] = "hello ";     // 7 + 3 bytes

   // strncat( str1, "Jimi", 1);    // Severe error: buffer overflow!
   // strncat( str2, "Jimi", 3);    // OK: "hello Jim"
   // strncat( str3, "Jim", 100);   // OK.

   // Or, using strncat_s(), with the variables defined above:
   int ret1, ret2, ret3;

   // set_constraint_handler_s(ignore_handler_s);
   ret1 = strncat_s(str1, sizeof(str1), "Jimi", 1);   // ret1 != 0 and
   // str1[0] == '\0'
   printf("ret1: %d    str1: %s\n", ret1, str1);

   ret2 = strncat_s(str2, sizeof(str2), "Jimi", 3);   // OK: ret2 == 0
   printf("ret2: %d    str2: %s\n", ret2, str2);

   ret3 = strncat_s(str3, sizeof(str3), "Jim", 100);  // OK: ret3 == 0
   printf("ret3: %d    str3: %s\n", ret3, str3);

   return 0;
}
