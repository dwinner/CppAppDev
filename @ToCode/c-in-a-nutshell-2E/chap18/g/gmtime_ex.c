// gmtime_ex.c : gmtime() example
// -------------------------------------------------------------

#include <time.h>   // struct tm *gmtime( const time_t *timer );
#include <stdio.h>
#include <string.h>

int main()
{
    time_t rawtime;
    struct tm utc_tm, local_tm, *ptr_tm;
    char buffer[1024] = "";

    time( &rawtime );                 // Get current time as an integer.

    ptr_tm = gmtime( &rawtime );      // Convert to UTC in a struct tm.
    memcpy( &utc_tm, ptr_tm, sizeof(struct tm) ); // Save a local copy.

    ptr_tm = localtime( &rawtime );   // Do the same for local time zone.
    memcpy( &local_tm, ptr_tm, sizeof(struct tm) );

    if ( strftime( buffer, sizeof(buffer),
                   "It's %A, %B %d, %Y, %R o'clock, UTC.", &utc_tm ) )
       puts( buffer );

    if ( strftime( buffer, sizeof(buffer),
                   "Here it's %A, %B %d, %Y, %R o'clock, UTC %z.", &local_tm ) )
       puts( buffer );

    return 0;
}
