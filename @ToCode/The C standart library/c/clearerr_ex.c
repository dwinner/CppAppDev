// clearerr_ex.c : clearerr() example
// -------------------------------------------------------------

#include <stdio.h>     // void clearerr(FILE *fp);
#include <stdlib.h>

int main()
{
    FILE *fp;
    int c;
    if ((fp = fopen("infile.dat", "r")) == NULL)
       fprintf(stderr, "Couldn't open input file.\n");
    else
    {
       c = fgetc(fp);   // fgetc() returns a character on success;
       if (c == EOF)    // EOF means either an error or end-of-file.
       {
          if ( feof(fp))
             fprintf(stderr, "End of input file reached.\n");
          else if ( ferror(fp))
             fprintf(stderr, "Error on reading from input file.\n");
          clearerr(fp);    // Same function clears both conditions.
       }
       else
       {  // Process the character that we read.
          /* ... */
       }
    }
    return 0;
}
