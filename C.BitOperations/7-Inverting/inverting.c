/**
 * Using bit operations to display binary
 * 
 */

#include <stdio.h>
#include <limits.h>

char* intToBits(int, char*);
void showBstr(const char*);
int invertStart(int num, int bits);

int main(void)
{
   char binStr[CHAR_BIT * sizeof(int) + 1];
   int number;

   puts("Enter integers and see them in binary.");
   puts("Non-numeric input terminates program.");
   while (scanf_s("%d", &number) == 1)
   {
      intToBits(number, binStr);
      printf("%d is\n", number);
      showBstr(binStr);
      putchar('\n');
      number = invertStart(number, 4);
      printf("Inverting the last 4 bits gives\n");
      showBstr(intToBits(number, binStr));
      putchar('\n');
   }
   puts("Bye!");

   return 0;
}

char* intToBits(int n, char* ps)
{
   static int size = 8 * sizeof(int);

   for (int i = size - 1; i >= 0; i--, n >>= 1)
      ps[i] = (01 & n) + '0';

   ps[size] = '\0';
   return ps;
}

/**
 * \brief Show binary string in blocks of 4
 * \param str Binary string
 */
void showBstr(const char* str)
{
   int i = 0;

   while (str[i]) /* not the null character */
   {
      putchar(str[i]);
      if (++i % 4 == 0 && str[i])
         putchar(' ');
   }
}

/**
 * \brief Invert the first bits-bit
 * \param num Number
 * \param bits Number of bits to be inverted from the first
 * \return Modified inverted number
 */
int invertStart(const int num, int bits)
{
   int mask = 0;
   int bitval = 1;

   while (bits-- > 0)
   {
      mask |= bitval;
      bitval <<= 1;
   }

   return num ^ mask;
}
