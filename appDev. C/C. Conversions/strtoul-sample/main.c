// strtoul_ex.c : strtoul() example
// -------------------------------------------------------------
// unsigned long strtoul( const char * restrict s,
//                        char ** restrict endptr,
//                        int base );

#include <stdlib.h>
#include <stdio.h>

int main()
{
   char dotted[] = "172.16.2.10", *ptr = dotted, *nextdot = NULL;
   unsigned long dest = 0;

   // This for loop uses stroul() to convert an IPv4 address from a
   // dotted-decimal string to a 32-bit integer value:
   for (int i = 0; i < 4; i++)
   {
      dest <<= 8UL;
      dest += strtoul(ptr, &nextdot, 10);
      ptr = nextdot + 1;
   }

   printf("The IPv4 address %s\n"
          "represents the 32-bit integer value %lu\n",
          dotted, dest);

   return 0;
}
