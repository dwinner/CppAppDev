// Example 3-1. Sample function error_exit()
// error_exit.c

#include <stdlib.h>
#include <stdio.h>

void error_exit(unsigned int error_n)   // Print a last error message
{                                       // and exit the program.
   char *error_msg[] =
      {
         "Unknown error code.\n",
         "Insufficient memory.\n",
         "Illegal memory access.\n"
      };
   unsigned int arr_len = sizeof(error_msg) / sizeof(char *);

   if (error_n >= arr_len)
   {
      error_n = 0;
   }

   fputs(error_msg[error_n], stderr);
   exit(EXIT_FAILURE);
}

#include <string.h>

#define PRG_NAME "EasyLine"

enum
{
   e_unknown,
   e_nomem,
   e_badaddr
};

int main()
{
   char msg[] = "The installation of " PRG_NAME
                " is now complete.";
   puts(msg);

   char *p = msg + 100;
   if (p > msg + strlen(msg))
   {
      error_exit(e_badaddr);
   }

   puts(p);
   /* . . . */

   return EXIT_SUCCESS;
}
