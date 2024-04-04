#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "bigram.h"

static int curWord = 2;
char wordVector[MAX_WORDS][MAX_WORD_LEN];
int bigramArray[MAX_WORDS][MAX_WORDS];
int sumVector[MAX_WORDS];

void loadWord(char *aWord, int anOrder)
{
   int wordIndex;
   static int lastIndex = START_SYMBOL;

   /* First, see if the aWord has already been recorded */
   for (wordIndex = 2; wordIndex < curWord; wordIndex++)
   {
      if (!strcmp(wordVector[wordIndex], aWord))
      {
         break;
      }
   }

   if (wordIndex == curWord)
   {
      if (curWord == MAX_WORDS)
      {
         printf("\nToo may words, increase MAX_WORDS\n\n");
         exit(-1);
      }

      /* Doesn't exist, add it in */
      strcpy(wordVector[curWord++], aWord);
   }

   /* At this point, we have a wordIndex that points to the current aWord
    * vector.
    */
   if (anOrder == FIRST_WORD)
   {
      bigramArray[START_SYMBOL][wordIndex]++;
      sumVector[START_SYMBOL]++;
   }
   else if (anOrder == LAST_WORD)
   {
      bigramArray[wordIndex][END_SYMBOL]++;
      bigramArray[END_SYMBOL][wordIndex]++;
      sumVector[END_SYMBOL]++;
   }
   else
   {
      bigramArray[lastIndex][wordIndex]++;
      sumVector[lastIndex]++;
   }

   lastIndex = wordIndex;
}

int nextWord(int aWord)
{
   int nextWord = (aWord + 1);
   int max = sumVector[aWord];
   int lim, sum = 0;

   lim = getRand(max) + 1;
   while (nextWord != aWord)
   {
      nextWord = nextWord % curWord;
      sum += bigramArray[aWord][nextWord];
      if (sum >= lim)
      {
         return nextWord;
      }

      nextWord++;
   }

   return nextWord;
}

int buildSentence(void)
{
   int word = START_SYMBOL;
   int max = 0;

   printf("\n");
   word = nextWord(word);
   while (word != END_SYMBOL)
   {
      printf("%s ", wordVector[word]);
      word = nextWord(word);
      max += getRand(12) + 1;
      if (max >= 100)
      {
         break;
      }
   }

   printf("%c.\n\n", 8);
   return 0;
}

void parseOptions(char **argv, int argc, int *dbg, char *aFileName)
{
   int opt, error = 1;

   *dbg = 0;
   if (argc > 1)
   {
      while ((opt = getopt(argc, argv, "vf:")) != -1)
      {
         switch (opt)
         {
            case 'v':
               *dbg = 1;
               break;

            case 'f':
               strcpy(aFileName, optarg);
               error = 0;
               break;

            default:
               error = 1;
         }
      }
   }

   if (error)
   {
      printf("\nUsage is : \n\n");
      printf("\t%s -f <filename> -v\n\n", argv[0]);
      printf("\t\t -f corpus filename\n\t\t -v verbose mode\n\n");
      exit(0);
   }
}

void parseFile(char *aFileName)
{
   FILE *fp;
   int inp, index = 0;
   char word[MAX_WORD_LEN + 1];
   int first = 1;

   fp = fopen(aFileName, "r");
   while (!feof(fp))
   {
      inp = fgetc(fp);
      if (inp == EOF)
      {
         if (index > 0)
         {
            word[index++] = 0;
            loadWord(word, LAST_WORD);
            index = 0;
         }
      }
      else if (((char) inp == 0x0d) || ((char) inp == 0x0a) || ((char) inp == ' '))
      {
         if (index > 0)
         {
            word[index++] = 0;
            if (first)
            {
               loadWord(word, FIRST_WORD);
               index = 0;
               first = 0;
            }
            else
            {
               loadWord(word, MIDDLE_WORD);
               index = 0;
            }
         }
      }
      else if (((char) inp == '.') || ((char) inp == '?'))
      {
         word[index++] = 0;
         loadWord(word, MIDDLE_WORD);
         loadWord(word, LAST_WORD);
         index = 0;
         first = 1;
      }
      else
      {
         if (((char) inp != 0x0a) && ((char) inp != ','))
         {
            word[index++] = (char) inp;
         }
      }
   }

   fclose(fp);
}

void emitMatrix(void)
{
   int x, y;

   printf("\n");
   for (x = 0; x < curWord; x++)
   {
      printf("%20s : ", wordVector[x]);
      for (y = 0; y < curWord; y++)
      {
         printf("%d ", bigramArray[x][y]);
      }

      printf(" : %d\n", sumVector[x]);
   }
}

int getCurrentWord(void)
{
   return curWord;
}

#pragma clang diagnostic pop