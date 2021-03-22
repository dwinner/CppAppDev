/**
 * Randomly generate the numbers between 1 and 1000 for user to guess.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void guessGame(void);
int isCorrect(int, int);

int main(void)
{
   srand(time(0));
   guessGame();
   return 0;
}

void guessGame(void)
{
   int answer, guess, response;

   do
   {
      answer = 1 + rand() % 1000;
      puts("I have a number between 1 and 1000.\n"
         "Can you guess my number?\n"
         "Please type your first guess.");
      printf("%s", "? ");
      scanf_s("%d", &guess);

      while (!isCorrect(guess, answer))
         scanf_s("%d", &guess);

      // prompt for another game
      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type ( 1=yes, 2=no )? ");
      scanf_s("%d", &response);
      puts("");
   }
   while (response == 1);
}

/**
 * @brief Returns true if g equals a
 * @param g number
 * @param a number
 * @return true if g equals a
 */
int isCorrect(int g, int a)
{
   if (g == a)
      return 1;

   // guess is incorrect; display hint
   printf("%s", g < a ? "Too low. Try again.\n? " : "Too high. Try again.\n? ");

   return 0;
}
