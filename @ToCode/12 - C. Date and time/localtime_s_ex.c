// gmtime_ex.c : gmtime() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>    // struct tm *localtime_s( const time_t * restrict timer,
                     //                         struct tm * restrict result);
#include <stdio.h>

int main()
{
    time_t now;    struct tm timeStruct;    char timeStr[26];

    time(&now);                           // Current time as an integer.

    // Convert to local time as a struct tm:
    if( localtime_s(&now, &timeStruct) != NULL)
    {
        timeStruct.tm_year += 1;          // One year later.
        if( asctime_s( timeStr, sizeof(timeStr), &timeStruct) == 0)
            printf("A year from today: %s", timeStr);
    }
    return 0;
}
