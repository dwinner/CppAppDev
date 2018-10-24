// mbsrtowcs_ex.c : mbsrtowcs() example
// -------------------------------------------------------------

#include <wchar.h>   // size_t mbsrtowcs( wchar_t * restrict dest, 
                     //                   const char ** restrict src,
                     //                   size_t n,
                     //                   mbstate_t * restrict state );
#include <string.h>
#include <locale.h>
#include <stdio.h>

int main()
{
   size_t result;

   char mbstring[ ] = "This is originally a multibyte string.\n";
   const char *mbsptr = mbstring;

   wchar_t widestring[256] = { L'\0' };

   mbstate_t state;
   memset( &state, '\0', sizeof state );

   printf( "The current locale is %s.\n", setlocale( LC_CTYPE, "" ));

   result = mbsrtowcs( widestring, &mbsptr, 256, &state );
   if ( result == (size_t)-1 )
   {
      fputs( "Encoding error in multibyte string", stderr );
      return -1;
   }
   else
   {
      printf( "Converted %u multibyte characters. The result:\n", result );
      printf( "%ls", widestring );
   }
   return 0;
}
