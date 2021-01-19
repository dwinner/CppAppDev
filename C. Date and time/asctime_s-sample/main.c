// asctime_s_ex.c : asctime_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__  1

#include <time.h>     // errno_t asctime_s(char *s, rsize_t maxsize,
//                   const struct tm *tmPtr);
#include <stdio.h>

int main(void)
{
#ifndef __STDC_LIB_EXT1__
   puts("Bounds-checking functions are not available.");
#else
   time_t now;
   struct tm timeStruct;
   char timeStr[26];

   time(&now);                       // Date and time as an integer.
   localtime_s(&now, &timeStruct);   // Convert to a structure.

   if( asctime_s( timeStr, sizeof(timeStr), &timeStruct) == 0)
      printf("Date and time: %s", timeStr);
#endif

   return 0;
}
