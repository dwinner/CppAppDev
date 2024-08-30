// isprint_ex.c : isprint() example
// And also an example for
// isalnum(), isalpha(), isblank(), iscntrl(), isdigit(),
// isgraph(), islower(), ispunct(), isspace().
// -------------------------------------------------------------

#include <ctype.h>    // int isprint( int c); int isalnum( int c); ...
#include <stdio.h>
#include <locale.h>

int main()
{
   unsigned int c;

//    setlocale(LC_CTYPE, "");
   printf("\nThe current locale for the 'is ...' functions is '%s'.\n",
          setlocale(LC_CTYPE, NULL));

   printf("Here is a table of the 'is ...' values for the characters"
          " from 0 to 127 in this locale:\n\n");

   for (c = 0; c < 128; c++)   // Loop iteration for each table row.
   {
      if (c % 24 == 0)        // Repeat table header every 24 rows.
      {
         printf("Code char alnum alpha blank cntrl digit graph lower"
                " print punct space\n");
         printf("---------------------------------------------------"
                "------------------\n");
      }

      printf("%4u %4c %3c %5c %5c %5c %5c %5c %5c %5c %5c %5c\n",
             c,                             // Print numeric character code.
             (isprint(c) ? c : ' '),  // Print the glyph, or a space
          // if it's not printable.
             (isalnum(c) ? 'X' : '-'),  // In a column for each category,
             (isalpha(c) ? 'X' : '-'),  // print X for yes or - for no.
             (isblank(c) ? 'X' : '-'),
             (iscntrl(c) ? 'X' : '-'),
             (isdigit(c) ? 'X' : '-'),
             (isgraph(c) ? 'X' : '-'),
             (islower(c) ? 'X' : '-'),
             (isprint(c) ? 'X' : '-'),
             (ispunct(c) ? 'X' : '-'),
             (isspace(c) ? 'X' : '-'));
   }  // end of loop for each character value

   return 0;
}
