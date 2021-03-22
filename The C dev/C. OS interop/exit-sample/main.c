// exit_ex.c : exit() example
// -------------------------------------------------------------

#include <stdlib.h>     // _Noreturn void exit( int status );
#include <stdio.h>

int main(int argc, char *argv[])
{
   FILE *f_in, *f_out;

   enum
   {
      X_OK = 0,
      X_ARGS,
      X_NOIN,
      X_NOOUT
   };

   if (argc != 3)
   {
      fprintf(stderr, "Usage: program input-file output-file\n");
      exit(X_ARGS);
   }

   f_in = fopen(argv[1], "r");
   if (f_in == NULL)
   {
      fprintf(stderr, "Unable to open input file.\n");
      exit(X_NOIN);
   }

   f_out = fopen(argv[2], "a+");

   if (f_out == NULL)
   {
      fprintf(stderr, "Unable to open output file.\n");
      exit(X_NOOUT);
   }

   /* ... read, process, write, close files ... */

   exit(X_OK);           //  return 0;
}
