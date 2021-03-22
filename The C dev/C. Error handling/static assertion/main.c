/**
 * Static assertion
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

_Static_assert(CHAR_BIT == 16, "Error in fact of 16-bit char");

int main()
{
   puts("Type char has 16 bits.");
   return EXIT_SUCCESS;
}
