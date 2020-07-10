// asctime_ex.c : asctime() example
// -------------------------------------------------------------

#include <time.h>    // char *asctime( struct tm *systime );
#include <stdio.h>

int main()
{
    time_t now;

    time( &now );          /* Get the time (seconds since 1/1/70) */
    printf( "Date: %.24s GMT\n", asctime( gmtime( &now ) ));

   return 0;
}
