//
// Bigram demonstration
//

#ifndef MARKOVMODELS_BIGRAM_H
#define MARKOVMODELS_BIGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_WORD_LEN   40
#define MAX_WORDS   1000

#define FIRST_WORD   0
#define MIDDLE_WORD   1
#define LAST_WORD   2

#define START_SYMBOL   0
#define END_SYMBOL   1

extern char wordVector[MAX_WORDS][MAX_WORD_LEN];
extern int bigramArray[MAX_WORDS][MAX_WORDS];
extern int sumVector[MAX_WORDS];

#define getSRand()   ((float)rand() / (float)RAND_MAX)
#define getRand(x)   (int)((x) * getSRand())

// Bigram array uses two special symbols -- start and end.
// These symbols act just like words, but indicate probabilities of
// word beginning or ending.

/**
 * @brief This function loads a aWord into the wordVector (if new) and then
 *  updates the bigram array based upon the current aWord sequence.
 * @param aWord Word
 * @param anOrder Order
 */
void loadWord(char *aWord, int anOrder);

/**
 * @brief his function gets the next aWord from the bigramArray based
 *  probabilistically on the current aWord.
 * @param aWord Word
 * @return The next aWord
 */
int nextWord(int aWord);

/**
 * @brief This function creates a random (probabilistic) sentence from the
 *  data contained within the bigram array.
 * @return Random sentence
 */
int buildSentence(void);

/**
 * @brief This function parses the command-line options and sets global
 *  flags accordingly.
 * @param argv Main's argv
 * @param argc Main's argc
 * @param dbg Debug flag
 * @param aFileName File name
 */
void parseOptions(char *argv[], int argc, int *dbg, char *aFileName);

/**
 * @brief This function parses the input file (corpus) and loads the words
 *  into the bigramArray as each is parsed.
 * @param aFileName File name
 */
void parseFile(char *aFileName);

/**
 * @brief This test function is used to emit the bigramArray.
 */
void emitMatrix(void);

int getCurrentWord(void);

#endif //MARKOVMODELS_BIGRAM_H
