// strtok_ex.c : strtok() example
// -------------------------------------------------------------
// char *strtok( char * restrict s1,
//               const char * restrict s2 );

#include <string.h>
#include <stdio.h>

int main()
{
   char *command, *arg1, *arg2, *comment;
   char line[] = " mul eax,[ebp+4] ; Multiply by y\n";

   command = strtok(line, " \t");   // First word, between spaces or tabs.
   arg1 = strtok(NULL, ",");      // From there to the comma is arg1.

   // (Trim off any spaces later.)
   arg2 = strtok(NULL, ";\n");    // From there to a semicolon or line end.
   comment = strtok(NULL, "\n\r\v\f");  // From there to end of line or page.
   printf("Command:      %s\n"
          "1st argument: %s\n"
          "2nd argument: %s\n"
          "Comment:      %s\n\n",
          command, arg1, arg2, comment);

   return 0;
}
