// fgetwc_ex.c : fgetwc() example
// -------------------------------------------------------------
// wint_t fgetwc( FILE *fp );

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
   char file_in[] = "local_in.txt",
       file_out[] = "local_out.txt";
   FILE *fp_in_wide, *fp_out_wide;
   wint_t wc;

   if (setlocale(LC_CTYPE, "") == NULL)
   {
      fwprintf(stderr,
               L"Sorry, couldn't change to the system's native locale.\n"),
          exit(1);
   }

   if ((fp_in_wide = fopen(file_in, "r")) == NULL)
   {
      fprintf(stderr, "Error opening the file %s\n", file_in), exit(2);
   }

   if ((fp_out_wide = fopen(file_out, "w")) == NULL)
   {
      fprintf(stderr, "Error opening the file %s\n", file_out), exit(3);
   }

   fwide(fp_in_wide, 1);            // Not strictly necessary, since first
   fwide(fp_out_wide, 1);           // file access also sets wide or byte mode.

   while ((wc = fgetwc(fp_in_wide)) != WEOF)
   {
      // ... process each wide character read ...

      if (fputwc((wchar_t) wc, fp_out_wide) == WEOF)
      {
         break;
      }
   }

   if (ferror(fp_in_wide))
   {
      fprintf(stderr, "Error reading the file %s\n", file_in);
   }
   
   if (ferror(fp_out_wide))
   {
      fprintf(stderr, "Error writing to the file %s\n", file_out);
   }

   return 0;
}
