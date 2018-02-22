// Fig. 8.23: fig08_23.c
// Using function strrchr
#include <stdio.h>
#include <string.h>

int main(void)
{ 
   // initialize char pointer
   const char *string1 = "A zoo has many animals including zebras";
          
   int c = 'z'; // character to search for
   
   printf("%s\n%s'%c'%s\"%s\"\n",
      "The remainder of string1 beginning with the",
      "last occurrence of character ", c,
      " is: ", strrchr(string1, c));
} 
