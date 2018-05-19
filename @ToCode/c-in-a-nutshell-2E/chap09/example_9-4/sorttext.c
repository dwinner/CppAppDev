// Example 9-4. A simple program to sort lines of text
// sorttext.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getLine(void);                // Reads a line of text
int str_compare(const void *, const void *);

#define NLINES_MAX 1000             // Maximum number of text lines.
char *linePtr[NLINES_MAX];          // Array of pointers to char.

int main()
{
   // Read lines:
   int n = 0;                       // Number of lines read.
   for ( ; n < NLINES_MAX && (linePtr[n] = getLine()) != NULL; ++n )
     ;

   if ( !feof(stdin) )              // Handle errors.
   {
      if ( n == NLINES_MAX )
         fputs( "sorttext: too many lines.\n", stderr );
      else
         fputs( "sorttext: error reading from stdin.\n", stderr );
   }
   else                             // Sort and print.
   {
      qsort( linePtr, n, sizeof(char*), str_compare );   // Sort.
      for ( char **p = linePtr; p < linePtr+n; ++p )     // Print.
         puts(*p);
   }
   return 0;
}

// Reads a line of text from stdin; drops the terminating
// newline character.
// Return value: A pointer to the string read, or
//               NULL at end-of-file, or if an error occurred.

#define LEN_MAX 512                 // Maximum length of a line.

char *getLine()
{
   char buffer[LEN_MAX], *linePtr = NULL;

   if ( fgets( buffer, LEN_MAX, stdin ) != NULL )
   {
      size_t len = strlen( buffer );

      if ( buffer[len-1] == '\n' )   // Trim the newline character.
         buffer[len-1] = '\0';
      else
         ++len;

      if ( (linePtr = malloc( len )) != NULL )   // Get memory for the line.
         strcpy( linePtr, buffer );  // Copy the line to the allocated block.
   }
   return linePtr;
}

// Comparison function for use by qsort().
// Arguments: Pointers to two elements in the array being sorted:
//            here, two pointers to pointers to char (char **).

int str_compare( const void *p1, const void *p2 )
{
   return strcmp( *(char **)p1, *(char **)p2 );
}
