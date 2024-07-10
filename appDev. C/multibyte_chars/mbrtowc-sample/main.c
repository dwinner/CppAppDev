// mbrtowc_ex.c : mbrtowc() example
// -------------------------------------------------------------
// size_t mbrtowc( wchar_t * restrict widebuffer,
//                 const char * restrict string,
//                 size_t maxsize,
//                 mbstate_t * restrict state );

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * Copies the multibyte string from s2 to s1, converting all the
 * characters to uppercase on the way.
 * Because there are no standard functions for case-mapping in multibyte
 * encodings, converts to and from the wide-character encoding (using the
 * current locale setting for the LC_CTYPE category). The source string
 * must begin in the initial shift state.
 * Returns: the number of bytes written;
 * or (size_t)-1 on an encoding error.
 */
size_t mbstoupper(char *s1, char *s2, size_t n)
{
   char *inptr = s2, *outptr = s1;
   wchar_t thiswc[1];
   size_t inresult, outresult;

   mbstate_t states[2], *instate = &states[0], *outstate = &states[1];

   memset(states, '\0', sizeof states);

   do
   {
      inresult = mbrtowc(thiswc, inptr, MB_CUR_MAX, instate);

      switch (inresult)
      {
         case (size_t) -2:     // The (MB_CUR_MAX) bytes at inptr do not make
            // a complete mb character. Maybe there is a
            // redundant sequence of shift codes. Treat the
            // same as an encoding error.
            *outptr = '\0';
            return (size_t) -1;

         case (size_t) -1:     // Found an invalid mb sequence at inptr:
            return inresult;  // pass the error to the caller.

         case 0:              // Got a null character. Make a last null wc.
            // The default action, with wcrtomb, does this
            // nicely, so *no break statement* necessary here.

         default:             // Read <result> mb characters to get one wide
            // character.
            /* Check for length limit before writing anything but a null.
               Note: Using inresult as an approximation for the output
               length.
               The actual output length could conceivably be different
               due to a different succession of state-shift sequences.
            */
            if ((outptr - s1) + inresult + MB_CUR_MAX > n)
            {   // i.e., if bytes written + bytes to write + termination > n,
               // then terminate now by simulating a null-character input.
               thiswc[0] = L'\0';
               inresult = 0;
            }

            inptr += inresult;

            if ((outresult = wcrtomb(outptr, (wchar_t) towupper(thiswc[0]), outstate)) == -1)
            {                               // Encoding error on output:
               *outptr = '\0';              // Terminate and return error.
               return outresult;
            }
            else
            {
               outptr += outresult;
            }
      }
   }
   while (inresult);              // Drop out after handling '\0'.

   return outptr - s1;
}

#include <locale.h>
#include <stdio.h>

int main()
{
   if (setlocale(LC_ALL, "en_US.utf-8") == NULL)
   {
      fputs("Unable to set the locale.\n", stderr);
   }

   printf("\nThe current locale is '%s'.\n", setlocale(LC_CTYPE, NULL));

   char strin[] = "Grüße", strout[64];
   size_t nByte = 0;

   nByte = mbstoupper(strout, strin, 64);

   if ((int) nByte < 0)
   {
      fputs("Error ...", stderr);
      return -1;
   }

   puts(strout);

   return 0;
}
