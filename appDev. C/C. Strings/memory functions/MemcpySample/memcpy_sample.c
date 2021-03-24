// Fig. 8.28: fig08_28.c
// Using function memcpy
#include <stdio.h>
#include <string.h>

int main(void)
{ 
   char s1[17]; // create char array s1
   char s2[] = "Copy this string"; // initialize char array s2

   memcpy(s1, s2, 17); 
   printf("%s\n%s\"%s\"\n", 
      "After s2 is copied into s1 with memcpy,",
      "s1 contains ", s1);
} 
