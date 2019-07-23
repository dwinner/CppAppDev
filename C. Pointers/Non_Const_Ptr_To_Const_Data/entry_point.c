/**
 * Printing a string one character at a time using
 * a non-constant pointer to constant data.
 */

#include <stdio.h>

void printCharacters(const char* sPtr);

int main(void)
{
   // initialize char array
   char string[] = "print characters of a string";

   puts("The string is:");
   printCharacters(string);
   puts("");
}

/**
 * @brief sPtr cannot be used to modify the character to which it points,
 * @param sPtr read-only pointer
 */
void printCharacters(const char* sPtr)
{
   // loop through entire string                            
   for (; *sPtr != '\0'; ++sPtr)
   {
      // no initialization   
      printf("%c", *sPtr);
   }
}
