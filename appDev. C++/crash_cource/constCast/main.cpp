#include <iostream>
#include <utility>

using namespace std;

void thirdPartyLibraryFunction(char *str)
{}

void f(const char *str)
{
   char *castedStr = const_cast<char *>(str);
   thirdPartyLibraryFunction(castedStr);
}

int main()
{
   string str{"C++"};
   const string &constStr{as_const(str)};
   f("force");

   return 0;
}
