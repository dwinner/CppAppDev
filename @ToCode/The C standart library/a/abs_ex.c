// abs_ex.c : abs() example
// -------------------------------------------------------------

#include <stdlib.h>       // int abs( int n );
                          // long labs( long n ); 
                          // long long labs( long long n ); 
#include <stdio.h>

int main()
{
    int amount = -1234;
    char currencysym[2] = "$";
    char sign[2] = "-";
    div_t dollarsandcents = { 0, 0 };

    if ( amount >= 0 )
       sign[0] = '\0';

    dollarsandcents = div(abs( amount ), 100 );

    printf( "The balance is %s%s%d.%2d\n", sign, currencysym,
             dollarsandcents.quot, dollarsandcents.rem );
   return 0;
}
