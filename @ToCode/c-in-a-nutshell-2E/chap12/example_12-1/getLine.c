// Example 12-1. The getLine() function
// getLine.c

#include <stdio.h>
#include <stdlib.h>

// Read a line of text from stdin into a dynamically allocated buffer.
// Replace the newline character with a string terminator.
// Arguments:    The maximum line length to read.
// Return value: A pointer to the string read, or
//               NULL if end-of-file was read or if an error occurred.

char *getLine( unsigned int len_max )
{
   char *linePtr = malloc( len_max+1 );  // Reserve storage for "worst case."
   if ( linePtr != NULL )
   {
     // Read a line of text and replace the newline characters with
     // a string terminator:
     int c = EOF;
     unsigned int i = 0;
     while ( i < len_max && ( c = getchar() ) != '\n' && c != EOF )
       linePtr[i++] = (char)c;
     linePtr[i] = '\0';

     if ( c == EOF && i == 0 )          // If end-of-file before any
     {                                  // characters were read,
        free( linePtr );                // release the whole buffer.
        linePtr = NULL;
     }
     else                               // Otherwise, release the unused portion.
        linePtr = realloc( linePtr, i+1 );           // i is the string length.
   }
   return linePtr;
}

int main()
{
   char *line;
   while(( line = getLine(128) ) != NULL )  // If we can read a line,
   {
      puts(line);                           // process the line,
      free( line );                         // then release the buffer.
   }
   return 0;
}
