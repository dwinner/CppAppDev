/**
 * Using the exit and atexit functions
 */

#include <stdio.h>
#include <stdlib.h>

void print(void);

_Noreturn int terminate_behavior(void);

int main(void)
{
   atexit(print); // register function print

   puts("Enter 1 to terminate program with function exit"
        "\nEnter 2 to terminate program normally");
   int answer; // user's menu choice
   scanf("%d", &answer);

   // call exit if answer is 1
   if (answer == 1)
   {
      terminate_behavior();
   }

   puts("\nTerminating program by reaching the end of main");
   return EXIT_SUCCESS;
}

void print(void)
{
   puts("Executing function print at program termination");
}

_Noreturn int terminate_behavior(void)
{
   puts("\nTerminating program with function exit");
   exit(EXIT_SUCCESS);
}
