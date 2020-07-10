// assert_ex.c : assert() example
// -------------------------------------------------------------

#include <assert.h>       // void assert( int expression );

int main()
{
    int units_in_stock = 10;
    int units_shipped = 9;
    /* ... */
    units_shipped++;
    units_in_stock--;
    /* ... */
    units_in_stock -= units_shipped;
    assert(units_in_stock >= 0);

    return 0;
}

