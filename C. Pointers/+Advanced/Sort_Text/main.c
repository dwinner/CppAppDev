/**
 * A simple program to sort lines of text
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads a line of text from stdin; drops the terminating newline character
 * @return line of text A pointer to the string read, or NULL at end-of-file,
 * or if an error occurred
 */
char *get_line(void);

/**
 * Comparison function for use by qsort()
 * @param p1 1st pointer to pointer to char being sorted
 * @param p2 2nd pointer to pointer to char being sorted
 * @return Comparison result for qsort
 */
int str_compare(const void *p1, const void *p2);

#define NLINES_MAX 1000             // Maximum number of text lines.

char *linePtr[NLINES_MAX];          // Array of pointers to char.

int main()
{
   // Read lines:
   int n = 0;                       // Number of lines read.
   for (; n < NLINES_MAX && (linePtr[n] = get_line()) != NULL; ++n);

   if (!feof(stdin))              // Handle errors.
   {
      fputs(n == NLINES_MAX
            ? "sorttext: too many lines.\n"
            : "sorttext: error reading from stdin.\n", stderr);
   }
   else                             // Sort and print.
   {
      qsort(linePtr, n, sizeof(char *), str_compare);   // Sort.
      for (char **p = linePtr; p < linePtr + n; ++p)     // Print.
      {
         puts(*p);
      }
   }

   return EXIT_SUCCESS;
}

#define LEN_MAX 512                 // Maximum length of a line.

char *get_line()
{
   char buffer[LEN_MAX], *linePtr = NULL;

   if (fgets(buffer, LEN_MAX, stdin) != NULL)
   {
      size_t len = strlen(buffer);

      if (buffer[len - 1] == '\n')   // Trim the newline character.
      {
         buffer[len - 1] = '\0';
      }
      else
      {
         ++len;
      }

      if ((linePtr = malloc(len)) != NULL)   // Get memory for the line.
      {
         strcpy(linePtr, buffer);  // Copy the line to the allocated block.
      }
   }

   return linePtr;
}

int str_compare(const void *p1, const void *p2)
{
   return strcmp(*(char **) p1, *(char **) p2);
}
