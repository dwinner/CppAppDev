/**
 * Uses enumerated values 
 * 
 */
#include <stdio.h>
#include <string.h>    // for strcmp()
#include <stdbool.h>   // C99 feature

enum spectrum
{
   Red,
   Orange,
   Yellow,
   Green,
   Blue,
   Violet
};

const char* Colors[] =
{
   "red",
   "orange",
   "yellow",
   "green",
   "blue",
   "violet"
};

#define LEN 30

int main(void)
{
   char choice[LEN];
   enum spectrum color;
   bool colorIsFound = false;

   puts("Enter a color (empty line to quit):");
   while (gets_s(choice, LEN) != NULL && choice[0] != '\0')
   {
      for (color = Red; color <= Violet; color++)
      {
         if (strcmp(choice, Colors[color]) == 0)
         {
            colorIsFound = true;
            break;
         }
      }

      if (colorIsFound)
         switch (color)
         {
         case Red:
            puts("Roses are red.");
            break;
         case Orange:
            puts("Poppies are orange.");
            break;
         case Yellow:
            puts("Sunflowers are yellow.");
            break;
         case Green:
            puts("Grass is green.");
            break;
         case Blue:
            puts("Bluebells are blue.");
            break;
         case Violet:
            puts("Violets are violet.");
            break;
         }
      else
         printf("I don't know about the color %s.\n", choice);

      colorIsFound = false;
      puts("Next color, please (empty line to quit):");
   }
   puts("Goodbye!");

   return 0;
}
