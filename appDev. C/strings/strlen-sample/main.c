// strlen_ex.c : strlen() example
// -------------------------------------------------------------
// size_t strlen( const char *s );

#include <string.h>
#include <stdio.h>

int main()
{
   char line[1024] = "This string could easily be hundreds of characters long.";
   char *read_ptr = line;
   int columns = 80;

   // While the text is longer than a row:
   while (strlen(read_ptr) > columns)
   {
      // print a row with a backslash at the end:
      printf("%.*s\\", columns - 1, read_ptr);
      read_ptr += columns - 1;
   }

   // Then print the rest with a newline at the end:
   printf("%s\n", read_ptr);

   return 0;
}
