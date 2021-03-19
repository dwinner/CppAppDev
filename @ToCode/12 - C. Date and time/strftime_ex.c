// strftime_ex.c : strftime() example
// -------------------------------------------------------------

#include <time.h>   // size_t strftime( char * restrict s, size_t n,
                    //                  const char * restrict format,
                    //                  const struct tm * restrict timeptr );
#include <stdio.h>

int main()
{
    time_t now;
    struct tm *localnow;
    char hdr_date[999] = "";

    time( &now );
    localnow = localtime( &now );

    if ( strftime( hdr_date, 78, "Date: %a, %d %b %Y %T %z", localnow ) )
        puts( hdr_date );
    else
        return -1;

    return 0;
}
