/**
 * Card shuffling and dealing program using structures
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES ((CARDS) / 4)

/**
 * @brief Card struct
 */
struct card
{
   const char* face;
   const char* suit;
};

/**
 * @see card
 */
typedef struct card Card;

void fillDeck(Card* wDeck, const char* wFace[], const char* wSuit[]);
void swapCard(Card* wDeck, size_t srcIdx, size_t destIdx);
void shuffle(Card* wDeck);
void deal(const Card* wDeck);

int main()
{
   Card deck[CARDS];

   const char* face[] =
   {
      "Ace",
      "Deuce",
      "Three",
      "Four",
      "Five",
      "Six",
      "Seven",
      "Eight",
      "Nine",
      "Ten",
      "Jack",
      "Queen",
      "King"
   };

   const char* suit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

   srand(time(NULL)); // randomize

   fillDeck(deck, face, suit); // load the deck with Cards
   shuffle(deck); // put Cards in random order
   deal(deck); // deal all 52 Cards

   return 0;
}

/**
 * @brief Place strings into Card structure
 *    @param wDeck Deck array
 *    @param wFace Face string array
 *    @param wSuit Suit string array
 */
void fillDeck(Card* const wDeck, const char* wFace[], const char* wSuit[])
{
   for (size_t i = 0; i < CARDS; ++i)
   {
      wDeck[i].face = wFace[i % FACES];
      wDeck[i].suit = wSuit[i / FACES];
   }
}

/**
 * @brief Swap the card
 *    @param wDeck Deck array
 *    @param srcIdx Source array index
 *    @param destIdx Destination array index
 */
void swapCard(Card* const wDeck, const size_t srcIdx, const size_t destIdx)
{
   const Card temp = wDeck[srcIdx];
   wDeck[srcIdx] = wDeck[destIdx];
   wDeck[destIdx] = temp;
}

/**
 * @brief Shuffle cards
 *    @param wDeck Deck array
 */
void shuffle(Card* const wDeck)
{
   for (size_t i = 0; i < CARDS; ++i)
   {
      const size_t j = rand() % CARDS;
      swapCard(wDeck, i, j);
   }
}

/**
 * @brief Deal cards
 *    @param wDeck Deck array
 */
void deal(const Card* const wDeck)
{
   for (size_t i = 0; i < CARDS; ++i)
   {
      printf("%5s of %-8s%s",
             wDeck[i].face,
             wDeck[i].suit,
             (i + 1) % 4 ? "  " : "\n");
   }
}
