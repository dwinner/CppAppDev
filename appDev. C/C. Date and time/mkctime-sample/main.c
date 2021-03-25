// mktime_ex.c : mkctime() example
// -------------------------------------------------------------
// time_t mktime( struct tm *timeptr );

#include <time.h>
#include <stdio.h>

int main()
{
   time_t seconds;
   struct tm sometime;

   sometime.tm_sec = 10;
   sometime.tm_min = 80;
   sometime.tm_hour = 40;
   sometime.tm_mday = 23;
   sometime.tm_mon = 1;
   sometime.tm_year = 105;
   sometime.tm_wday = 11;
   sometime.tm_yday = 111;
   sometime.tm_isdst = -1;

   seconds = mktime(&sometime);

   if (seconds == -1)
   {
      printf("mktime() couldn't make sense of its input.\n");
      return -1;
   }

   printf("The return value, %ld, represents %s",
          (long) seconds, ctime(&seconds));

   printf("The structure has been adjusted as follows:\n"
          "tm_sec   == %d\n"
          "tm_min   == %d\n"
          "tm_hour  == %d\n"
          "tm_mday  == %d\n"
          "tm_mon   == %d\n"
          "tm_year  == %d\n"
          "tm_wday  == %d\n"
          "tm_yday  == %d\n"
          "tm_isdst == %d\n",

          sometime.tm_sec,
          sometime.tm_min,
          sometime.tm_hour,
          sometime.tm_mday,
          sometime.tm_mon,
          sometime.tm_year,
          sometime.tm_wday,
          sometime.tm_yday,
          sometime.tm_isdst);

   printf("The structure now represents %s", asctime(&sometime));

   return 0;
}
