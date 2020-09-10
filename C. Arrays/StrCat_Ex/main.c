/**
 * strcat() function example
 */

/**
 * Appends a copy of the 2nd string to the end of the 1st string
 * @param s1 Destination string
 * @param s2 String to be appended
 * @return A pointer to the 1st string, now concatenated with the 2nd string
 */
char *strcat_(char *restrict s1, const char *restrict s2)
{
   char *rtnPtr = s1;
   while (*s1 != '\0')  // find the end of string s1
   {
      ++s1;
   }

   while ((*s1++ = *s2++) != '\0')  // the 1st character from s2
      ;                             // replaces the terminator of s1

   return rtnPtr;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   char msg[32] = "Hello, ", name[32];

   printf("Please enter your name: ");
   if (scanf(" %31[^\n]", name) == EOF)
   {
      return EXIT_FAILURE;
   }

   if (sizeof(msg) <= (strlen(msg) + strlen(name)))
   {
      puts("Message array is too small");
   }
   else
   {
      strcat_(msg, name);
      puts(msg);
   }

   return EXIT_SUCCESS;
}
