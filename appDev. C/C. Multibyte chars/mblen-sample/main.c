// mblen_ex.c : mblen() example
// -------------------------------------------------------------
// int mblen( const char *s, size_t maxsize );

#include <stdlib.h>
#include <wchar.h>
#include <string.h>

/**
 * mbsrcat: multibyte string restartable concatenation.
 * Appends s2 to s1, respecting final shift state of destination string,
 * indicated by *p_s1state. String s2 must start in the initial shift
 * state.
 * Returns: number of bytes written, or (size_t)-1 on encoding error.
 * Max. total length (incl. terminating null byte) is <= n;
 * stores ending state of concatenated string in *s1state.
 */
size_t mbsrcat(char *restrict s1, char *restrict s2, mbstate_t *restrict p_s1state, size_t n)
{
   int result;
   size_t i = strlen(s1);
   size_t j = 0;

   if (i >= n - (MB_CUR_MAX + 1))
   {   // Sanity check: room for 1 multibyte
      // char + string terminator.
      return 0;
   }                    // Report 0 bytes written.

   // Shift s1 down to initial state:

   if (!mbsinit(p_s1state))     // If not initial state, then append
   {                               // shift sequence to get initial state.
      if ((result = wcrtomb(s1 + i, L'\0', p_s1state)) == -1)
      {                            // Encoding error:
         s1[i] = '\0';             // Try restoring termination.
         return (size_t) -1;        // Report error to caller.
      }
      else
      {
         i += result;
      }
   }

   // Copy only whole multibyte characters at a time.
   // Get length of next char w/o changing state:
   while ((result = mblen(s2 + j, MB_CUR_MAX)) <= (n - (1 + i)))
   {
      if (result == 0)
      {
         break;
      }

      if (result == -1)
      {                        // Encoding error:
         s1[i] = '\0';         // Terminate now.
         return (size_t) -1;    // Report error to caller.
      }

      // Next character fits; copy it and update state:
      strncpy(s1 + i, s2 + j, mbrlen(s2 + j, MB_CUR_MAX, p_s1state));
      i += result;
      j += result;
   }

   s1[i] = '\0';

   return j;
}

#include <locale.h>
#include <stdio.h>

int main()
{
   if (setlocale(LC_ALL, "") == NULL)
   {
      fputs("Unable to set the locale.\n", stderr);
   }

   printf("\nThe current locale is '%s'.\n", setlocale(LC_CTYPE, NULL));

   char str1[100] = "";
   mbstate_t mbstate = {0};
   size_t nChars = 0;

   nChars = mbsrcat(str1, "große ", &mbstate, sizeof(str1));
   if ((int) nChars < 0)
   {
      fputs("Error ...", stderr);
      return -1;
   }

   printf("%zu characters.\n", nChars);

   nChars = mbsrcat(str1, "Füße", &mbstate, sizeof(str1));
   if ((int) nChars < 0)
   {
      fputs("Error ...", stderr);
      return -1;
   }

   printf("%zu characters.\n", nChars);

   puts(str1);

   return 0;
}
