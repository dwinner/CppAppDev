// Example 2-1. 
// limits.c: Display the value ranges of char and int.
// ---------------------------------------------------
#include <stdio.h>
#include <limits.h>     // Contains the macros CHAR_MIN, INT_MIN, etc.

int main()
{
  printf("Storage sizes and value ranges of the types char and int\n\n");

  printf("The type char is %s.\n\n", CHAR_MIN < 0 ? "signed" :"unsigned");

  printf(" Type   Size (in bytes)   Minimum         Maximum\n"
         "---------------------------------------------------\n");
  printf(" char %8zu %20d %15d\n", sizeof(char), CHAR_MIN, CHAR_MAX );
  printf(" int  %8zu %20d %15d\n", sizeof(int), INT_MIN, INT_MAX );

  return 0;
}
