#include "library.h"

#include <iostream>

void hello()
{
   std::cout << "Hello, World!" << std::endl;
}

int functionInDLL(const wchar_t *p)
{
   std::wcout << std::format(L"The following string was received by C++: '{}'", p) << std::endl;
   return 42;    // Return some value...
}
