/**
 * ctime_ex.c : ctime() example:
 * errno_t ctime_s(char *s, rsize_t maxsize, const time_t *timer);
 */

#define __STDC_WANT_LIB_EXT1__ 1

#include <time.h>
#include <stdio.h>

int main()
{
#ifndef __STDC_LIB_EXT1__
   puts("Bounds-checking functions are not available.");
#else
   time_t now = 0;
    char timeStr[26];

    time(&now);                   // Date and time as an integer.
    if (ctime_s( timeStr, sizeof(timeStr), &now) == 0)
       printf("Date and time: %s", timeStr);
#endif

   return 0;
}
