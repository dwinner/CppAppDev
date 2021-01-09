// snprintf_ex.c : snprintf() example
// -------------------------------------------------------------

#include <stdio.h>   // int snprintf( char * restrict dest, size_t n,
                     //               const char * restrict format, ... );

int main()
{
    char buffer[80];
    double x = 1234.5, y = 678.9, z = -753.1, a = x * y + z;
    int output_len = 0;

    output_len = snprintf( buffer, 80, "For the input values %lf, %lf,"
                           " and %lf,\nthe result was %lf.\n",
                           x, y, z, a );
    puts( buffer );
    if ( output_len >= 80 )
       fprintf( stderr, "Output string truncated! Lost %d characters.\n",
                output_len - 79 );
    return 0;
}
