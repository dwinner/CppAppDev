// at_quick_exit_ex.c : at_quick_exit() example
// -------------------------------------------------------------

#include <stdlib.h>       // int at_quick_exit( void (*func)( void ));
#include <stdio.h>

void nexit(void)
{
   puts("Program terminated normally.");
}

void qexit(void)
{
   puts("Programm terminated by \"quick_exit()\".");
}

int main(void)
{
   int a = -1;
   atexit(nexit);
   at_quick_exit(qexit);

   if (a < 0)
   {
      quick_exit(EXIT_FAILURE);
   }

   return 0;
}
