// strspn_ex.c : strspn() example
// -------------------------------------------------------------
// int strspn( const char *s1, const char *s2 );

#include <string.h>
#include <stdio.h>

int main()
{
   char wordin[256];
   double val;

   puts("Enter a floating-point number, please:");
   scanf("%s", wordin);

   int index = strspn(wordin, "+-0123456789eE.");
   if (index < strlen(wordin))
   {
      printf("Sorry, but the character %c is not permitted.\n",
             wordin[index]);
   }
   else
   {
      sscanf(wordin, "%lg", &val);
      printf("You entered the value %g\n", val);
   }

   return 0;
}
