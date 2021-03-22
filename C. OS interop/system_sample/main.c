// system_ex.c : system() example
// -------------------------------------------------------------

#include <stdlib.h>    // int system( const char *s );
#include <stdio.h>

int main()
{
   if (system(NULL))
   {
      system("echo \"Shell: $SHELL; process ID: $$\"");
   }
   else
   {
      printf("No command processor available.\n");
   }

   return 0;
}
