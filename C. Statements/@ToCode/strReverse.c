// strReverse.c : The function strReverse() 
// reverses the order of the characters in a string.

#include <string.h>

void strReverse( char* str)
{
   char ch;
   for ( size_t i = 0, j = strlen(str)-1; i < j; ++i, --j )
       ch = str[i], str[i] = str[j], str[j] = ch;
}

#include <stdio.h>

int main()
{
  char text[] = "in reversed order";
  strReverse( text);
  puts(text);

  return 0;
}
