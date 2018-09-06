/**
 * strcpy() demo
 */

#include <stdio.h>
#include <string.h>

#define SIZE      40
#define LIM       5
#define WORDS     "beast"
#define TARGSIZE  7

void strcpyDemo();
void strcpyWithOffset();
void strncpyDemo();

int main()
{
   strcpyDemo();
   strcpyWithOffset();
   strncpyDemo();

   puts("Press any key to continue...");
   getchar();
   return 0;
}

void strcpyDemo()
{
   char qwords[LIM][SIZE];
   char temp[SIZE];
   int i = 0;

   printf("Enter %d words beginning with q:\n", LIM);
   while (i < LIM && gets_s(temp, SIZE))
   {
      if (temp[0] != 'q')
      {
         printf("%s doesn't begin with q!\n", temp);
      }
      else
      {
         strcpy_s(qwords[i], SIZE, temp);
         i++;
      }
   }

   puts("Here are the words accepted:");
   for (i = 0; i < LIM; i++)
   {
      puts(qwords[i]);
   }
}

void strcpyWithOffset()
{
   const char* orig = WORDS;
   char copy[SIZE] = "Be the best that you can be.";
   errno_t errno;

   puts(orig);
   puts(copy);
   errno = strcpy_s(copy + 7, SIZE, orig);   // result: Be the beast
   if (errno == 0)
   {
      puts(copy);
   }
}

void strncpyDemo()
{
   char qwords[LIM][TARGSIZE];
   char temp[SIZE];
   int i = 0;

   printf("Enter %d words beginning with q:\n", LIM);
   while (i < LIM && gets_s(temp,SIZE))
   {
      if (temp[0] != 'q')
      {
         printf("%s doesn't begin with q!\n", temp);
      }
      else
      {
         strncpy_s(qwords[i], SIZE, temp, TARGSIZE - 1);
         qwords[i][TARGSIZE - 1] = '\0';
         i++;
      }
   }

   puts("Here are the words accepted:");
   for (i = 0; i < LIM; i++)
      puts(qwords[i]);
}
