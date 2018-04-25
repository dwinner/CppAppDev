/**
 * Using ADT-style linked list
 */

#include "List.h"
#include <stdlib.h>
#include <stdio.h>

static void showMovies(Item item);

int main()
{
   List movies;
   Item temp;

   /* initialize */
   initializeList(&movies);
   if (isFull())
   {
      fprintf(stderr, "No memoty available! Bye!\n");
      exit(EXIT_FAILURE);
   }

   /* gather and store */
   puts("Enter first movie title:");
   while (gets_s(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
   {
      puts("Enter your rating <0-10>:");
      scanf_s("%d", &temp.rating);
      while (getchar() != '\n')
      {
      }

      if (!addItem(temp, &movies))
      {
         fprintf(stderr, "Problem allocating memory\n");
         break;
      }

      if (isFull())
      {
         puts("The list is now full.");
         break;
      }

      puts("Enter the next movie (empty line to stop):");
   }

   /* display */
   if (isEmpty(&movies))
   {
      printf("No data entered.");
   }
   else
   {
      printf("Here is the movie list:\n");
      traverse(&movies, showMovies);
   }

   printf("You entered %d movies.\n", getItemCount(&movies));

   /* clean up */
   makeEmpty(&movies);
   printf("Bye!\n");

   return EXIT_SUCCESS;
}

void showMovies(const Item item)
{
   printf("Movie: %s Rating: %d\n",
          item.title,
          item.rating);
}
