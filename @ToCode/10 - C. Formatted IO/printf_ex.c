// printf_ex.c : printf() example
// -------------------------------------------------------------

#include <stdio.h>      // int printf( const char * restrict format, ... );
#include <math.h>
#include <assert.h>

void print_line( double x);

int main()
{
    double pi = 3.1415926;
    double bignumber = 8 * 8 * 8 * pi * pi * pi;
    printf("512 times pi cubed equals %.2e, or %.2a.\n",
                                      bignumber, bignumber);

    print_line( 11.22);
    return 0;
}

// The print_line function illustrates the use of the %n conversion specification
// to count the characters in the output string:
void print_line( double x)
{
    int n1, n2;
    printf("x = %5.2f exp(x) = %n%10.5f%n\n", x, &n1, exp(x), &n2);
    assert( n2-n1 <= 10);           // Did printf() stretch the field width?
}
