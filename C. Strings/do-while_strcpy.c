// Example 6-4. A strcpy() function using do … while
// do-while_strcpy.c :
// Copy string s2 to string s1.
// ----------------------------

char *strcpy_( char* restrict s1, const char* restrict s2 )
{
   int i = 0;
   do
      s1[i] = s2[i];           // The loop body: copy each character
   while ( s2[i++] != '\0' );  // End the loop if we just copied a '\0'.
   return s1;
}

#include <stdio.h>

int main()
{
  char src[] = "strcpy example ...",
       dest[sizeof(src)];
  strcpy_( dest, src);
  puts(dest);

  return 0;
}
