/**
 * Displaying a histogram
 */
#include <stdio.h>
#define SIZE 5

int main(void)
{
   int n[SIZE] = {19, 3, 15, 7, 11};

   printf("%s%13s%17s\n", "Element", "Value", "Histogram");

   // for each element of array n, output a bar of the histogram
   for (size_t i = 0; i < SIZE; ++i)
   {
      printf("%7u%13d      ", i, n[i]);

      for (int j = 0; j <= n[i]; ++j) // print one bar
      {
         printf("%c", '*');
      }

      puts(""); // end a histogram bar with a newline
   }

   return 0;
}
