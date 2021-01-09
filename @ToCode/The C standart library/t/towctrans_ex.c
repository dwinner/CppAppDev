// towctrans_ex.c : towctrans() example
// -------------------------------------------------------------

#include <wctype.h>  // wint_t towctrans( wint_t wc, wctrans_t desc );
#include <wchar.h>

int main()
{
   wint_t before = L'\0', after = L'\0';
   wctrans_t mapping;
   mapping = wctrans("toupper");

   while (( before = getwchar() ) != WEOF )
   {
       after = towctrans( before, mapping );
       putwchar( after );
       if ( after == L'Q' )
          break;
    }
    return 0;
}
