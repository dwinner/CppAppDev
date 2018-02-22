/**
 * Reads in-strings and sort them
 */

#include <stdio.h>
#include <string.h>

#define SIZE   81    /* string length limit, including \0 */
#define LIM    20    /* maximum number of lines to be read */

void sortStrings(char* strings[], int num); /* string-sort function */

int main(void)
{
   char input[LIM][SIZE]; /* array to store input */
   char* ptstr[LIM]; /* array of pointer variables */
   int ct = 0; /* input count */

   printf("Input up to %d lines, and I will sort them.\n", LIM);
   printf("To stop, press the Enter key at a line's start.\n");

   while (ct < LIM && gets_s(input[ct], LIM) != NULL && input[ct][0] != '\0')
   {
      ptstr[ct] = input[ct]; /* set ptrs to strings */
      ct++;
   }

   sortStrings(ptstr, ct); /* string sorter */
   puts("\nHere the sorted list:\n");
   for (int k = 0; k < ct; k++)
   {
      puts(ptstr[k]); /* sorted pointers */
   }

   return 0;
}

void sortStrings(char* strings[], const int num)
{
   for (int top = 0; top < num - 1; top++)
   {
      for (int seek = top + 1; seek < num; seek++)
      {
         if (strcmp(strings[top], strings[seek]) > 0)
         {
            char* temp = strings[top];
            strings[top] = strings[seek];
            strings[seek] = temp;
         }
      }
   }
}
