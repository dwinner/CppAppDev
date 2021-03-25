// sprintf_ex.c : sprintf() example
// -------------------------------------------------------------
// int sprintf( char * restrict dest,
//              const char * restrict format, ... );

#include <stdio.h>

int main()
{
   char buffer[80];
   double x = 1234.5, y = 678.9, z = -753.1, a = x * y + z;
   int output_len = 0;

   output_len = sprintf(buffer, "For the input values %lf, %lf, and %lf,"
                                "\nthe result was %lf.\n",
                        x, y, z, a);
   puts(buffer);
   if (output_len >= 80)
   {
      fprintf(stderr, "Output string overflowed by %d characters.\n"
                      "The variables x, y, z and a may have been corrupted:\n"
                      "x now contains %lf, y %lf, z %lf, and a %lf.\n",
              output_len - 79, x, y, z, a);
   }

   return 0;
}
