// Fig. 10.2: fig10_02.c
// Structure member operator and 
// structure pointer operator
#include <stdio.h>

// card structure definition            
struct card {                           
   char *face; // define pointer face   
   char *suit; // define pointer suit   
}; 

int main(void)
{ 
   struct card aCard; // define one struct card variable   

   // place strings into aCard
   aCard.face = "Ace";   
   aCard.suit = "Spades";

   struct card *cardPtr = &aCard; // assign address of aCard to cardPtr

   printf("%s%s%s\n%s%s%s\n%s%s%s\n", aCard.face, " of ", aCard.suit,
      cardPtr->face, " of ", cardPtr->suit,                           
      (*cardPtr).face, " of ", (*cardPtr).suit);                 
}
