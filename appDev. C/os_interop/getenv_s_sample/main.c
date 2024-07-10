// getenv_s_ex.c : getenv_s() example
// -------------------------------------------------------------
// errno_t getenv_s( size_t * restrict len, char * restrict value, rsize_t maxsize, const char * restrict name );

#define __STDC_WANT_LIB_EXT1__ 1

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
   const char *env_str = getenv("PATH");

   /*
   char envStr[512];
   size_t len;

   if (getenv_s(&len, envStr, sizeof(envStr), "PATH") == 0)
   {
      printf("PATH variable (%zu characters): \n%s\n", len, envStr);
   }
   else if (len > 0)
   {
      printf("The PATH variable (%zu characters) is more than "
             "%zu bytes long.\n", len, sizeof(envStr));
   }
   else
   {
      printf("PATH variable not found.\n");
   }*/

   printf("%s", env_str);

   return 0;
}
