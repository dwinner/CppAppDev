// atexit_ex.c : atexit() example
// -------------------------------------------------------------

#include <stdlib.h>       // int atexit( void (*func)( void ));
#include <stdio.h>

int main()
{
   void f1(void), f2(void);

   printf("Registering the \"at-exit\" functions f1 and f2:");

   if (atexit(f1) || atexit(f2))
   {
      printf(" failed.\n");
   }
   else
   {
      printf(" done.\n");
   }

   printf("Exiting now.\n");

   exit(0);                        // Equivalent to return 0;
}

void f1(void)
{
   printf("Running the \"at-exit\" function f1().\n");
}

void f2(void)
{
   printf("Running the \"at-exit\" function f2().\n");
}
