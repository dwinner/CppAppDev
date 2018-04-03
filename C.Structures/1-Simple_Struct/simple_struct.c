/**
 * Structure member operator
 * and structure ponter operator
 */
#include <stdio.h>

struct card
{
   char* face;
   char* suit;
};

typedef struct card Card;

int main(/*int argc, char* argv[]*/)
{
   Card aCard;

   aCard.face = "Ace";
   aCard.suit = "Spades";

   Card* pCard = &aCard;

   printf("%s%s%s\n%s%s%s\n%s%s%s\n",
          aCard.face, " of ", aCard.suit,
          pCard->face, " of ", pCard->suit,
          (*pCard).face, " of ", (*pCard).suit);

   return 0;
}
