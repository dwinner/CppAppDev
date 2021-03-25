// strftime_ex.c : strftime() example
// -------------------------------------------------------------
// size_t strftime( char * restrict s, size_t n,
//                  const char * restrict format,
//                  const struct tm * restrict timeptr );

#include <time.h>
#include <stdio.h>

int main()
{
   time_t now;
   struct tm *local_now;
   char hdr_date[999] = "";

   time(&now);
   local_now = localtime(&now);

   if (strftime(hdr_date, 78, "Date: %a, %d %b %Y %T %z", local_now))
   {
      puts(hdr_date);
   }
   else
   {
      return -1;
   }

   return 0;
}
