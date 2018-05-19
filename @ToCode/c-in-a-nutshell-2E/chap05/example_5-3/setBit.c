// Example 5-3. Using a shift operation to manipulate a bit mask
// setBit.c

#include <stdio.h>
#include <limits.h>

// Function setBit()
// Sets the bit at position p in the mask m.
// Uses CHAR_BIT, defined in limits.h, for the number of bits in a byte.
// Return value: The new mask with the bit set, or the original mask
//               if p is not a valid bit position.

unsigned int setBit( unsigned int mask, unsigned int p )
{
   if ( p >= CHAR_BIT * sizeof(int) )
      return mask;
   else
      return mask | (1 << p);
}

int main()
{
   unsigned int a = 6;      // Bit pattern: 0 0 ... 0 0 0 1 1 0
   printf("a = %u\n", a);

   a = setBit( a, 4);       // Bit pattern: 0 0 ... 0 1 0 1 1 0
   printf("setBit(a,4) = %u\n", a);      // 22 = 16 + 6

   return 0;
}
