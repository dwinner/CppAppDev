// fclose_ex.c : fclose() example
// -------------------------------------------------------------
// int fclose( FILE *fp );

#include <stdio.h>

/* Print a file to the console, line by line. */

int main()
{
   FILE *fp_infile;
   char linebuffer[512];

   if ((fp_infile = fopen("input.dat", "r")) == NULL)
   {
      fprintf(stderr, "Couldn't open input file.\n");
      return -1;
   }

   while (fgets(linebuffer, sizeof(linebuffer), fp_infile) != NULL)
   {
      fputs(linebuffer, stdout);
   }

   if (!feof(fp_infile))
   {         // This means "if not end of file"
      fprintf(stderr, "Error reading from input file.\n");
   }

   if (fclose(fp_infile) != 0)
   {
      fprintf(stderr, "Error closing input file.\n");
      return -2;
   }

   return 0;
}
