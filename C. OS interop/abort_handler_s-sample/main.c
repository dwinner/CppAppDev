// abort_handler_s_ex.c : abort_handler_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__  1

#include <stdlib.h>  // void abort_handler_s( const char * restrict msg,
//                       void * restrict ptr,
//                       errno_t error);
#include <string.h>
#include <stdio.h>

int main(void)
{
#ifdef __STDC_LIB_EXT1__
   char name[15]= "NN";

   set_constraint_handler_s(abort_handler_s);
   strcpy_s( name, sizeof(name), "Abraham Lincoln");
#else
   puts("Bounds-checking functions are not available.");
#endif

   return 0;
}
