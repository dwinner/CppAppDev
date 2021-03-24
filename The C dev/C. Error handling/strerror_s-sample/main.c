// strerror_s_ex.c : strerror_s() example
// -------------------------------------------------------------
// errno_t strerror_s(char *s, rsize_t maxsize, errno_t errnum);

#define __STDC_WANT_LIB_EXT1__ 1

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

int main()
{
   double x = -1.0, y = 0;
   // ...
   errno = 0;
   y = sqrt(x);
   if (errno == EDOM)
   {
      char msg[30] = "";
      strerror_s(msg, sizeof(msg), errno);
      fprintf(stderr, "sqrt: %s\n", msg);
   }

   // ...
   return 0;
}
