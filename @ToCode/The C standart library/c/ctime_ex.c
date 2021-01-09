// ctime_ex.c : ctime() example
// -------------------------------------------------------------

#include <time.h>    // char *ctime( const time_t *seconds );
#include <stdio.h>

void logerror(int errorcode)
{
    time_t eventtime;

    time(&eventtime);
    fprintf( stderr, "%s: Error number %d occurred.\n",
             ctime(&eventtime), errorcode );
}

int main()
{
   logerror(23);
   return 0;
}
