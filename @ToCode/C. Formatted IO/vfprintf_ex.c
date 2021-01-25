// vfprintf_ex.c : vfprintf() example
// -------------------------------------------------------------

#include <stdio.h>   
#include <stdarg.h>
// int vfprintf( FILE * restrict fp, const char * restrict format, va_list argptr );
// int vprintf( const char * restrict format, va_list argptr );
// int vsprintf( char * restrict buffer, const char * restrict format,
//               va_list argptr );
// int vsnprintf( char * restrict buffer, size_t n, const char * restrict format, //                va_list argptr );

#include <time.h>

// write_log appends a line to the log file associated with the
// FILE pointer fp_log.
// The format string and optional arguments are the same as for printf().

FILE *fp_log;
 
void write_log(const char *function_name, unsigned int line_num,
               const char *format_str, ...)
{
    if ( fp_log == NULL)
       return;
    time_t timestamp = time(NULL);
    va_list argptr;

    // Set argptr to the first optional argument:
    va_start( argptr, format_str);

    // First print the timestamp, function name, and line number:
    fprintf( fp_log, "%.8s %s (line %u): ",
                     ctime(&timestamp)+11, function_name, line_num);
    // Then print the rest of the message:
    vfprintf( fp_log, format_str, argptr);
}

void myFunc( int param)
{
    write_log( __func__, __LINE__, "param = %d\n", param);
    /* ... */
}

int main()
{
    fp_log = stderr;
    myFunc( 777);    
    return 0;
}
