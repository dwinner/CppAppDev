/**
 * String comparing
 */

#include <stdio.h>
#include <string.h>  /* declares strcmp() */

#define ANSWER "Grant"
#define MAX 40

int main()
{
   char try[MAX];

   puts("Who is buried in Grant's tomb?");
   gets_s(try, MAX);
   while (strcmp(try, ANSWER) != 0)
   {
      puts("No, that's wrong. Try again.");
      gets_s(try, MAX);
   }

   puts("That's right!");

   return 0;
}
