/**
 * Using the character and string conversion specifiers
 */
#include <stdio.h>

int main(void)
{
   const char character = 'A'; // initialize char
   printf("%c\n", character);

   printf("%s\n", "This is a string");

   char string[] = "This is a string"; // initialize char array
   printf("%s\n", string);

   const char* stringPtr = "This is also a string"; // char pointer
   printf("%s\n", stringPtr);

   return 0;
}
