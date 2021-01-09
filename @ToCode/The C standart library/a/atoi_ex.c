// atoi_ex.c : atoi() example
// -------------------------------------------------------------

#include <stdlib.h>       // int atoi( const char *s );
                          // long atol( const char *s );
                          // long long atoll( const char *s );
#include <stdio.h>

int main()
{
    char *s = " -135792468.00 Balance on Dec. 31";
    printf("\"%s\" becomes %ld\n", s, atol(s));

    return 0;
}
