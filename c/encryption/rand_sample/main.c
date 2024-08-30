// rand_ex.c : rand() example
// -------------------------------------------------------------
// int rand( void );

#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

int main()
{
   printf("Think of a number between one and twenty.\n"
          "Press Enter when you're ready.");
   getchar();

   srand((unsigned) time(NULL));
   for (int i = 0; i < 3; i++)     // We get three guesses.
   {
      printf("Is it %u? (y or n) ", 1 + rand() % 20);
      if (tolower(getchar()) == 'y')
      {
         printf("Ha! I knew it!\n");
         exit(0);
      }

      // Discard newline character.
      getchar();
   }

   printf("I give up.\n");

   return 0;
}
