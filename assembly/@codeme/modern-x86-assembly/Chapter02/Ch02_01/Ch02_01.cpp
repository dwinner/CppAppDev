//-----------------------------------------------------------------------------
// Ch02_01.cpp
//-----------------------------------------------------------------------------

#include "Ch02_01.h"

int main()
{
    int a = 10;
    int b = 40;
    int c = 9;
    int d = 6;

    int r1 = (a + b) - (c + d) + 7;
    int r2 = AddSubI32_a(a, b, c, d);

    DisplayResults(a, b, c, d, r1, r2);
    return 0;
}