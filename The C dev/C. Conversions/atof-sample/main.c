// atof_ex.c : atof() example
// -------------------------------------------------------------

#include <stdlib.h>       // double atof( const char *s );
#include <stdio.h>

int main()
{
   char string[] = " -1.02857e+2 \260C";  // symbol for degrees Celsius
   double z;

   z = atof(string);
   printf("\"%s\" becomes %.2f\n", string, z);

   return 0;
}
