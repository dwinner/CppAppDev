// strtod_ex.c : strtod() example
// -------------------------------------------------------------
// double strtod( const char * restrict s,
//                char ** restrict endptr );

#include <stdlib.h>
#include <stdio.h>

int main()
{
   char in[1024], *this = in, *next = in;
   double val;

   puts("Enter some floating-point numbers, please:");
   scanf("%[^\n]", in);

   puts("Here are the values you entered:");
   while (1)
   {
      val = strtod(this, &next);
      if (next == this)
      {     // Means no conversion was possible.
         break;
      }

      printf("\t%g\n", val);
      this = next;            // Try again with the rest of the input string.
   }

   puts("Done.");

   return 0;
}
