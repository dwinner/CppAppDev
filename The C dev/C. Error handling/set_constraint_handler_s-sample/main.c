// set_constraint_handler_s_ex.c : set_constraint_handler_s() example
// -------------------------------------------------------------------
// constraint_handler_t set_constraint_handler_s(constraint_handler_t handler);

#define __STDC_WANT_LIB_EXT1__ 1

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

// Use a custom handler:
void myConstraintHandler(const char *msg, void *ptr, errno_t error)
{
   printf("A runtime constraint violation "
          "occurred: \n%s; ", msg);
   printf("error code: %d\n", error);
   fflush(stdout);
   exit(error);
}

void func(const char *str)
{
   constraint_handler_t prevHandler = set_constraint_handler_s(myConstraintHandler);
   printf_s("The argument: %s\n", str);        // Error if str
   // is a null pointer.
   int len = strlen(str);
   char str2[len];
   strcpy_s(str2, len, str);    // Error: str2 is one byte too short.
   // . . .
   set_constraint_handler_s(prevHandler);
}

int main()
{
   func("Hi");
   return 0;
}
