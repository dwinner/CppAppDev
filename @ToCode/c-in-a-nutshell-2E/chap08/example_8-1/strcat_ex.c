// Example 8-1. Function strcat()
// strcat_ex.c

// The function strcat_() appends a copy of the second string
// to the end of the first string.
// Arguments:    Pointers to the two strings.
// Return value: A pointer to the first string,
//               now concatenated with the second string.

char *strcat_( char * restrict s1, const char * restrict s2 )
{
   char *rtnPtr = s1;
   while ( *s1 != '\0' )               // Find the end of string s1.
      ++s1;
   while (( *s1++ = *s2++ ) != '\0' )  // The first character from s2
     ;                                 // replaces the terminator of s1.
   return rtnPtr;
}

#include <stdio.h>
#include <string.h>          // for strlen() 

int main()
{
   char msg[32] = "Hello, ", name[32];

   printf("Please enter your name: ");
   if( scanf(" %31[^\n]", name) == EOF)
      return 1;
   
   if ( sizeof(msg) <= ( strlen(msg) + strlen(name) ) )
      puts("Message array is too small.");
   else
   {
      strcat_( msg, name );
      puts( msg);
   }
   return 0;
}

