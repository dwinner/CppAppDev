/**
 * Using bit operations to display binary
 */
#include <stdio.h>
#include <limits.h>

char* intToBits(int, char*);
void showBstr(const char*);

int main(void)
{
   char binStr[8 * sizeof(int) + 1];
   int number;

   puts("Enter integers and see them in binary.");
   puts("Non-numeric input terminates the program.");

   while (scanf_s("%d", &number) == 1)
   {
      intToBits(number, binStr);
      printf("%d is ", number);
      showBstr(binStr);
      putchar('\n');
   }

   puts("Bye!");

   return 0;
}

/**
 * \brief Convert integer to bit view
 * \param n Number
 * \param ps String to fill
 * \return String filled with bits
 */
char* intToBits(int n, char* ps)
{
   static int size = CHAR_BIT * sizeof(int);

   for (int i = size - 1; i >= 0; i--, n >>= 1)
   {
      ps[i] = (01 & n) + '0';
   }

   ps[size] = '\0';

   return ps;
}

/**
 * \brief Show bits
 * \param str String
 */
void showBstr(const char* str)
{
   int i = 0;

   while (str[i])
   {
      putchar(str[i]);
      if (++i % 4 == 0 && str[i])
      {
         putchar(' ');
      }
   }
}
