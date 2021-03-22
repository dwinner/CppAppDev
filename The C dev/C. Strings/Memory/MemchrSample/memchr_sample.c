// Fig. 8.31: fig08_31.c
// Using function memchr
#include <stdio.h>
#include <string.h>

int main(void)
{ 
   const char *s = "This is a string"; // initialize char pointer

   printf("%s\'%c\'%s\"%s\"\n", 
      "The remainder of s after character ", 'r', 
      " is found is ", (char *) memchr(s, 'r', 16));
}
