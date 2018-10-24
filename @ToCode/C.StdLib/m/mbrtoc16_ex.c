// mbrtoc16_ex.c : mbrtoc16() example
// -------------------------------------------------------------

#include <uchar.h>     // size_t mbrtoc16( char16_t * restrict pc16,
                       //                  const char * restrict s,
                       //                  size_t n, 
                       //                  mbstate_t * restrict state );
//#include <stdlib.h>
#include <string.h>

// The function mbsToC16s() uses mbrtoc16() to convert a string of
// multibyte characters into a string of 16-bit characters
// (typically in UTF-16 encoding).
// Return value: the number of char16_t characters produced, or
//               -1 if an error occurred.

int mbsToC16s( const char *mbStr, char16_t *c16Str, size_t len)
{
   if( mbStr == NULL || c16Str == NULL || len == 0)   // Sanity checks.
      return -1;

   mbstate_t mbstate = {0};
   char16_t c16;
   int count = 0, i = 0, rv = 0,
       nBytes = (int)strlen(mbStr)+1;

   do {
      rv = (int)mbrtoc16( &c16, mbStr+i, nBytes-i, &mbstate);
      switch( rv)
      {
        case 0:  c16Str[count] = 0; i = nBytes;   // End of string.
                 break;
        case -1:                                  // Encoding error.
        case -2: count = -1;
                 break;
        default:
           if( count < (int)len-1 )
           {
              c16Str[count++] = c16;
              if( rv > 0) i += rv;                // rv != -3
           }
           else count = -1;
      }
   } while( count > 0 && i < nBytes);

   return count;
}

#include <locale.h>
#include <stdio.h>

int main(void)
{
   if( setlocale(LC_ALL, "en_US.utf8") == NULL)
      fputs("Unable to set the locale.\n", stderr);

   char *u8Str = u8"Grüße";
   char16_t c16Str[100];
   int nChars = 0;

   nChars = mbsToC16s( u8Str, c16Str, 100);
   if( nChars < 0)
      fputs("Error ...", stderr);
   else
   {
      printf("%d UTF-16 characters.\n", nChars);
      // ...
   }
   return 0;
}
