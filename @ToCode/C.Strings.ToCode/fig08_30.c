// Fig. 8.30: fig08_30.c
// Using function memcmp
#include <stdio.h>
#include <string.h>

int main(void)
{ 
   char s1[] = "ABCDEFG"; // initialize char array s1
   char s2[] = "ABCDXYZ"; // initialize char array s2
        
   printf("%s%s\n%s%s\n\n%s%2d\n%s%2d\n%s%2d\n",
      "s1 = ", s1, "s2 = ", s2,
      "memcmp(s1, s2, 4) = ", memcmp(s1, s2, 4),
      "memcmp(s1, s2, 7) = ", memcmp(s1, s2, 7),
      "memcmp(s2, s1, 7) = ", memcmp(s2, s1, 7));
}
