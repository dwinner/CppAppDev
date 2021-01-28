// fgetws_ex.c : fgetws() example
// -------------------------------------------------------------
// wchar_t *fgetws( wchar_t * restrict buffer, int n, FILE * restrict fp );

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main()
{
   FILE *fp_in_wide;
   wchar_t buffer[4096];
   wchar_t *line = buffer;

   if (setlocale(LC_CTYPE, "") == NULL)
   {
      fwprintf(stderr, L"Sorry, couldn't change to the system's native locale.\n");
      return -1;
   }

   if ((fp_in_wide = fopen("local_in.txt", "r")) == NULL)
   {
      perror("Opening input file");
      return -1;
   }

   fwide(fp_in_wide, 1);

   line = fgetws(buffer, sizeof(buffer), fp_in_wide);
   if (line == NULL)
   {
      perror("Reading from input file");
   }
   else if (fputws(line, stdout) < 0)
   {
      perror("Writing to stdout");
   }

   return 0;
}
