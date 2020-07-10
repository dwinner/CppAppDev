/**
 * Converting a string to uppercase using a
 * non-constant pointer to non-constant data.
 */

#include <stdio.h>
#include <ctype.h>

void convertToUppercase(char* sPtr);

int main()
{
   char string[] = "cHaRaCters and $32.98"; // initialize char array

   printf("The string before conversion is: %s", string);
   convertToUppercase(string);
   printf("\nThe string after conversion is: %s\n", string);

   return 0;
}

void convertToUppercase(char* sPtr)
{
   while (*sPtr != '\0')
   {
      *sPtr = toupper(*sPtr);
      ++sPtr;
   }
}
