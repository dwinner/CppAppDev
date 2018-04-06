/**
 * Displaying an unsigned int in bits
 */
#include <stdio.h>
#include <limits.h>
#define CPU_WORD_SIZE (sizeof(void*)*CHAR_BIT)
#define DEFAULT_DISPLAY_MASK (1 << (CPU_WORD_SIZE - 1))

void displayBits(unsigned int value);

int main()
{
   unsigned int x;

   printf("%s", "Enter a nonnegative int: ");
   scanf_s("%u", &x);

   displayBits(x);

   return 0;
}

/**
 * @brief Display bits of an unsigned int value
 *    @param value 
 */
void displayBits(unsigned value)
{
   printf("%10u = ", value);
   const unsigned int mask = DEFAULT_DISPLAY_MASK;

   for (unsigned int c = 1; c <= CPU_WORD_SIZE; ++c)
   {
      putchar(value & mask ? '1' : '0');
      value <<= 1;

      if (c % CHAR_BIT == 0)
      {
         putchar(' ');
      }
   }

   putchar('\n');
}
