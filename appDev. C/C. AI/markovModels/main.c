#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
/*
 * This is the main function for the bigram demonstration. It parses the
 * options from the command line, initializes the bigramArray, parses the
 * corpus file and then emits a random (probabilistic) sentence.
 */

#include <stdio.h>
#include "bigram.h"

int main(int argc, char *argv[])
{
   char filename[40];
   int debug = 0;
   parseOptions(argv, argc, &debug, filename);
   srand(time(NULL));
   memset(bigramArray, 0, MAX_WORDS * MAX_WORDS * sizeof(int));
   strcpy(wordVector[0], "<START>");
   strcpy(wordVector[1], "<END>");
   parseFile(filename);
   if (debug)
   {
      emitMatrix();
   }

   printf("unique = %d\n", getCurrentWord());
   buildSentence();

   return 0;
}

#pragma clang diagnostic pop