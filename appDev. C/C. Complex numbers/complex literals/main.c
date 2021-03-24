/**
 * Complex literals
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_TITLE 41
#define MAX_AUTL  31

struct book
{
   char title[MAX_TITLE];
   char author[MAX_AUTL];
   float value;
};

int main()
{
   struct book readFirst;
   int score;
   printf("Enter the rating: ");
   scanf("%d", &score);
   readFirst = score >= 34
               ? (struct book)
                  {
                     "Crime and punishment",
                     "Feodor Dostoevsky",
                     11.25
                  }
               : (struct book)
                  {
                     "The beautiful hat of Mr. Bouncy",
                     "Fred Uinsom",
                     5.99
                  };

   printf("Your setting ratings:\n");
   printf("%s by %s: $%.2f\n",
          readFirst.title,
          readFirst.author,
          readFirst.value);

   return EXIT_SUCCESS;
}
