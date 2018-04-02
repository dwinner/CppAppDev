/**
 * Using a scan set
 */
#include <stdio.h>

int main(void)
{
   char z[9]; // define array z

   printf("%s", "Enter string: ");
   scanf_s("%8[aeiou]", z); // search for set of characters

   printf("The input was \"%s\"\n", z);

   return 0;
}
