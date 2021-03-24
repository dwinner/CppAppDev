/**
 * Using an array of structures
 */

#include <stdlib.h>
#include <stdio.h>

#define TSIZE  45 /* Size of array to hold the title */
#define FMAX   5  /* Maximum number of film titles */

struct film
{
   char title[TSIZE];
   int rating;
};

int main()
{
   struct film movies[FMAX];
   int i = 0;
   int j;

   puts("Enter first movie title:");
   while (i < FMAX
      && gets_s(movies[i].title, TSIZE) != NULL
      && movies[i].title[0] != '\0')
   {
      puts("Enter your rating <0-10>");
      scanf_s("%d", &movies[i++].rating);
      while (getchar() != '\n')
      {
      }

      puts("Enter next movie title (empty line to stop):");
   }

   printf(i == 0 ? "No data entered. " : "Here is the movie list:\n");

   for (j = 0; j < i; j++)
   {
      printf("Movie: %s  Rating: %d\n",
             movies[j].title,
             movies[j].rating);
   }

   printf("Bye!\n");

   return EXIT_SUCCESS;
}
