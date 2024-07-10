// wcslen_ex.c : wcslen() example
// -------------------------------------------------------------
// size_t wcslen( const wchar_t *s );

#include <wchar.h>

int main()
{
   wchar_t line[1024] =
       L"This string could easily be 400 or 500 characters long. "
       L"This string could easily be 400 or 500 characters long. "
       L"\n";
   wchar_t *read_ptr = line;

   int columns = 80;
   while (wcslen(read_ptr) > columns)  // While remaining text is too long,
   {                                    // print a chunk with a final
      wprintf(L"%.*ls\\\n", columns - 1, read_ptr);  // backslash and newline.
      read_ptr += columns - 1;
   }

   wprintf(L"%ls\n", read_ptr);     // Print the rest, ending with a newline.

   return 0;
}
