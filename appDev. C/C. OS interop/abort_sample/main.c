// abort_ex.c : abort() example
// -------------------------------------------------------------

#include <stdlib.h>       // _Noreturn void abort( void );
#include <stdio.h>

struct record
{
   long id;
   int data[256];
   struct record *next;
};

void abort_ex()
{
   /* ... */
   struct record *new = (struct record *) malloc(sizeof(struct record));
   if (new != NULL)                   // Check whether malloc failed!
   {
      fprintf(stderr, "%s: out of memory!\n", __func__);
      abort();
   }
   else
   {
      puts("working ...");
      // a fatal error occurs:
      abort();                          // abort the program.
   }
}

int main()
{
   abort_ex();
   return 0;
}

