/**
 * Using signal handling
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

void signalHandler(int signalValue);

int main()
{
   signal(SIGINT, signalHandler);   // register signal handler
   srand(time(NULL));

   for (int i = 1; i <= 100; ++i)
   {
      int x = 1 + rand() % 50;   // generate random number to raise SIGINT

      if (x == 25)
      {
         raise(SIGINT);
      }

      printf("%4d", i);

      if (i % 10 == 0)
      {
         printf("%s", "\n");
      }
   }

   return EXIT_SUCCESS;
}

void signalHandler(int signalValue)
{
   printf("%s%d%s\n%s",
          "\nInterrupt signal (", signalValue,
          ") received.",
          "Do you wish to continue (1 = yes or 2 = no)? ");
   int response;
   scanf("%d", &response);

   while (response != 1 && response != 2)
   {
      printf("%s", "(1 = yes or 2 = no)");
      scanf("%d", &response);
   }

   // determine whether it's time to exit
   if (response == 1)
   {
      // reregister signal handler for next SIGINT
      signal(SIGINT, signalHandler);
   }
   else
   {
      exit(EXIT_SUCCESS);
   }
}
