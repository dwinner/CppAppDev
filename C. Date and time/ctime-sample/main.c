/**
 * ctime_ex.c : ctime() example
 * char *ctime( const time_t *seconds );
 */

#include <time.h>
#include <stdio.h>

void logerror(int errorCode)
{
   time_t eventtime;

   time(&eventtime);
   fprintf(stderr, "%s: Error number %d occurred.\n",
           ctime(&eventtime),
           errorCode);
}

int main()
{
   logerror(23);
   return 0;
}
