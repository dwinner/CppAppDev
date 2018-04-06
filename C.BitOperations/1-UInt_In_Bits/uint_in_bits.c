/**
 * Displaying an unsigned int in bits
 */
#include <stdio.h>
#include <limits.h>
#define CPU_WORD_SIZE (sizeof(void*)*CHAR_BIT)
#define DEFAULT_DISPLAY_MASK (1 << (CPU_WORD_SIZE - 1))

void getBits(unsigned value, char bitArray[CPU_WORD_SIZE]);

int main()
{
   char bitArray[CPU_WORD_SIZE];
   unsigned int x;

   printf("%s", "Enter a nonnegative int: ");
   scanf_s("%u", &x);

   getBits(x, bitArray);

   for (unsigned int i = 0; i < CPU_WORD_SIZE; ++i)
   {
      putchar(bitArray[i]);

      if ((i + 1) % CHAR_BIT == 0)
      {
         putchar(' ');
      }
   }

   return 0;
}

/**
 * \brief Get bits
 * \param value Value
 * \param bitArray Array of bits to be set
 */
void getBits(unsigned value, char bitArray[CPU_WORD_SIZE])
{
   for (unsigned int bitIndex = 0; bitIndex < CPU_WORD_SIZE; ++bitIndex)
   {
      bitArray[bitIndex] = value & DEFAULT_DISPLAY_MASK ? '1' : '0';
      value <<= 1;
   }
}
